let animation = null;
let files = [];
let directoryHandle = null;
let folderOpened = false;
let selectedObject = null;
let selectedKeyframe = null;

function componentToHex(c) {
  var hex = c.toString(16);
  return hex.length == 1 ? "0" + hex : hex;
}

function rgbToHex(r, g, b) {
  return "#" + componentToHex(r) + componentToHex(g) + componentToHex(b);
}

function hexToRgb(hex) {
  var result = /^#?([a-f\d]{2})([a-f\d]{2})([a-f\d]{2})$/i.exec(hex);
  return result
    ? {
        r: parseInt(result[1], 16),
        g: parseInt(result[2], 16),
        b: parseInt(result[3], 16),
      }
    : null;
}

const openFile = async (ext = "*") => {
  return new Promise((resolve) => {
    let file = document.createElement("input");
    file.type = "file";
    file.accept = ext;

    file.addEventListener("change", () => {
      files = Array.from(file.files);
      if (files.length > 0) {
        content = files[0];
        resolve(content);
      } else {
        resolve(null);
      }
    });
    file.click();
  });
};

const saveFile = async (fileName, content) => {
  if (directoryHandle == null) {
    loadAnimation();
  }
  directoryHandle
    .getFileHandle(fileName, { create: true })
    .then((fileHandle) => {
      fileHandle.createWritable().then((writer) => {
        writer.write(content);
        writer.close();
      });
    });
};

const saveAnimation = async () => {
  await saveFile("animation.json", JSON.stringify(animation));
};

const loadAnimation = async () => {
  let files = await openDirectory();
  for (let file of files || []) {
    if (file.name == "animation.json") {
      animation = await file.text();
      animation = JSON.parse(animation);
      break;
    }
  }
  if (animation == null) {
    animation = {
      duration: 5000,
      prodFps: 30,
      previewFps: 5,
      objects: [
        {
          id: "camera",
          type: "camera",
          name: "Camera",
          keyframes: {
            0: {
              position: [0, 0, 0],
              rotation: [0, 0, 0],
            },
          },
        },
      ],
    };
    saveAnimation();
  }
  reloadObjects();
  $("#durationRange").val(0);
};

const openDirectory = async (mode = "readwrite") => {
  // Feature detection. The API needs to be supported
  // and the app not run in an iframe.
  const supportsFileSystemAccess =
    "showDirectoryPicker" in window &&
    (() => {
      try {
        return window.self === window.top;
      } catch {
        return false;
      }
    })();
  // If the File System Access API is supported…
  if (supportsFileSystemAccess) {
    let directoryStructure = undefined;

    // Recursive function that walks the directory structure.
    const getFiles = async (dirHandle, path = dirHandle.name) => {
      const dirs = [];
      const files = [];
      for await (const entry of dirHandle.values()) {
        const nestedPath = `${path}/${entry.name}`;
        if (entry.kind === "file") {
          files.push(
            entry.getFile().then((file) => {
              file.directoryHandle = dirHandle;
              file.handle = entry;
              return Object.defineProperty(file, "webkitRelativePath", {
                configurable: true,
                enumerable: true,
                get: () => nestedPath,
              });
            })
          );
        } else if (entry.kind === "directory") {
          dirs.push(getFiles(entry, nestedPath));
        }
      }
      return [
        ...(await Promise.all(dirs)).flat(),
        ...(await Promise.all(files)),
      ];
    };

    try {
      // Open the directory.
      const handle = await showDirectoryPicker({
        mode,
      });
      // Get the directory structure.
      directoryHandle = handle;
      directoryStructure = getFiles(handle, undefined);
    } catch (err) {
      if (err.name !== "AbortError") {
        console.error(err.name, err.message);
      }
    }
    return directoryStructure;
  }
  // Fallback if the File System Access API is not supported.
  return new Promise((resolve) => {
    const input = document.createElement("input");
    input.type = "file";
    input.webkitdirectory = true;

    input.addEventListener("change", () => {
      let files = Array.from(input.files);
      resolve(files);
    });
    if ("showPicker" in HTMLInputElement.prototype) {
      input.showPicker();
    } else {
      input.click();
    }
  });
};

async function addObject() {
  let modelFile = await openFile(".obj");
  let materialFile = await openFile(".mtl");

  if (modelFile == null || materialFile == null) {
    alert("You need to select a model and a material file");
    return;
  }

  let objId = "obj-" + animation.objects.length;
  let modelFilename = objId + ".obj";
  let materialFilename = objId + ".mtl";

  let modelContent = await modelFile.text();
  // Replace the material file name in the model file, starting with mtllib word
  modelContent = modelContent.replace(
    /mtllib\s+.*\.mtl/g,
    "mtllib " + materialFilename
  );

  await saveFile(objId + ".obj", modelContent);
  await saveFile(objId + ".mtl", materialFile);

  let name = "Object";
  let split = modelContent.split("\n");
  for (let line of split) {
    if (line.startsWith("o ")) {
      name = line.substring(2);
      break;
    }
  }

  animation.objects.push({
    id: "obj-" + animation.objects.length,
    type: "object",
    name: name,
    modelFile: modelFilename,
    materialFile: materialFilename,
    keyframes: {
      0: {
        position: [0, 0, 0],
        rotation: [0, 0, 0],
        scale: [1, 1, 1],
      },
    },
  });
  reloadObjects();
  saveAnimation();
}

function addLight() {
  animation.objects.push({
    id: "light-" + animation.objects.length,
    type: "light",
    name: "Light",
    ambient: [0.2, 0.2, 0.2],
    diffuse: [0.8, 0.8, 0.8],
    specular: [0.8, 0.8, 0.8],
    color: [1, 1, 1],
    keyframes: {
      0: {
        position: [0, 0, 0],
      },
    },
  });
  reloadObjects();
  saveAnimation();
}

const updateConfig = () => {
  let duration = $("#configModal .duration").val();
  let prodFps = $("#configModal .prodFps").val();
  let previewFps = $("#configModal .previewFps").val();

  if (duration) {
    animation.duration = duration;
  }
  if (prodFps) {
    animation.prodFps = prodFps;
  }
  if (previewFps) {
    animation.previewFps = previewFps;
  }
  reloadObjects();
  saveAnimation();
};

function changeFrame() {
  $("#frameLabel").text(`Frame ${$("#durationRange").val()}`);
}

const reloadObjects = async () => {
  $("#configModal .duration").val(animation.duration);
  $("#configModal .prodFps").val(animation.prodFps);
  $("#configModal .previewFps").val(animation.previewFps);
  $("#durationRange").attr("max", animation.duration);

  $("#listObjects").empty();
  for (let object of animation.objects) {
    $("#listObjects").append(`<li
          class="list-group-item d-flex justify-content-between align-items-center list-group-item-action ${
            selectedObject === object.id ? "active" : ""
          }" objectId="${object.id}" onclick="selectObj(this)">
          ${
            object.type == "camera"
              ? '<i class="bi bi-camera-video-fill"></i>'
              : ""
          }
          ${object.type == "object" ? '<i class="bi bi-box2-fill"></i>' : ""}
            ${
              object.type == "light"
                ? '<i class="bi bi-brightness-high-fill"></i>'
                : ""
            }
          ${object.name}
          <button class="btn badge badge-danger badge-pill" ${
            object.type === "camera" ? "disabled" : ""
          }>X</button>
      </li>`);
  }
  if (selectedObject != null) {
    $(`#objProperty`).css("visibility", "visible");
  } else {
    $(`#objProperty`).css("visibility", "hidden");
  }
};

function selectObj(element) {
  element = $(element);
  let id = element.attr("objectId");
  selectedObject = id;
  selectedKeyframe = null;
  reloadObjects();
  reloadProperties();
}

function getPreviousKeyframe(keyframe) {
  let keys = Object.keys(
    animation.objects.find((o) => o.id === selectedObject).keyframes
  );
  let index = keys.indexOf(keyframe);
  if (index == 0) {
    return keyframe;
  } else {
    return keys[index - 1];
  }
}

function reloadProperties() {
  let obj = animation.objects.find((o) => o.id === selectedObject);
  if (obj == null) {
    return;
  }
  $("#objProperty #objectName").val(obj.name);
  if (obj.type == "light") {
    $("#objProperty #lightProps").show();
    $("#objProperty #lightProps .lightAmbient .x").val(obj.ambient[0]);
    $("#objProperty #lightProps .lightAmbient .y").val(obj.ambient[1]);
    $("#objProperty #lightProps .lightAmbient .z").val(obj.ambient[2]);

    $("#objProperty #lightProps .lightDiffuse .x").val(obj.diffuse[0]);
    $("#objProperty #lightProps .lightDiffuse .y").val(obj.diffuse[1]);
    $("#objProperty #lightProps .lightDiffuse .z").val(obj.diffuse[2]);

    $("#objProperty #lightProps .lightSpecular .x").val(obj.specular[0]);
    $("#objProperty #lightProps .lightSpecular .y").val(obj.specular[1]);
    $("#objProperty #lightProps .lightSpecular .z").val(obj.specular[2]);

    $("#objProperty #lightProps .lightColor input").val(
      rgbToHex(obj.color[0] * 255, obj.color[1] * 255, obj.color[2] * 255)
    );
  } else {
    $("#objProperty #lightProps").hide();
  }
  $("#objProperty #listKeyframes").empty();
  for (let keyframe in obj.keyframes) {
    let keyframeData = obj.keyframes[keyframe];
    $("#objProperty #listKeyframes")
      .append(`<li class="list-group-item d-flex justify-content-between align-items-center list-group-item-action ${
      selectedKeyframe == keyframe ? "active" : ""
    }" onclick="selectKeyframe(this)" frame="${keyframe}">
        Frame ${keyframe}
        <span>
            ${
              keyframeData.position
                ? '<span class="badge badge-primary badge-pill">Position</span>'
                : ""
            }
            ${
              keyframeData.rotation
                ? '<span class="badge badge-primary badge-pill">Rotation</span>'
                : ""
            }
            ${
              keyframeData.scale
                ? '<span class="badge badge-primary badge-pill">Scale</span>'
                : ""
            }
        </span>
    </li>`);
  }
  if (selectedKeyframe != null) {
    $("#objProperty #keyframeProps").css("visibility", "visible");
    let selectedObjectData = animation.objects.find(
      (o) => o.id === selectedObject
    );
    let keyframeData = obj.keyframes[selectedKeyframe];
    let prevKeyframe = getPreviousKeyframe(selectedKeyframe);
    $("#objProperty #keyframeProps").empty();
    $("#objProperty #keyframeProps").append(`<div class="col">
    <label>Position</label>
    <div class="row framePosition" style="margin: 0">
      <input
        type="text"
        class="form-control col-sm-4"
        placeholder="X" value="${
          keyframeData.position ? keyframeData.position[0] : ""
        }" onchange="updateKeyframe()"
      />
      <input
        type="text"
        class="form-control col-sm-4"
        placeholder="Y" value="${
          keyframeData.position ? keyframeData.position[1] : ""
        }" onchange="updateKeyframe()"
      />
      <input
        type="text"
        class="form-control col-sm-4"
        placeholder="Z" value="${
          keyframeData.position ? keyframeData.position[2] : ""
        }" onchange="updateKeyframe()"
      />
    </div>
  </div>`);

    if (selectedObjectData.type != "light") {
      $("#objProperty #keyframeProps").append(`<div class="col">
        <label>Rotation</label>
        <div class="row frameRotation" style="margin: 0">
            <input
            type="text"
            class="form-control col-sm-4"
            placeholder="X" value="${
              keyframeData.rotation ? keyframeData.rotation[0] : ""
            }" onchange="updateKeyframe()"
            />
            <input
            type="text"
            class="form-control col-sm-4"
            placeholder="Y" value="${
              keyframeData.rotation ? keyframeData.rotation[1] : ""
            }" onchange="updateKeyframe()"
            />
            <input
            type="text"
            class="form-control col-sm-4"
            placeholder="Z" value="${
              keyframeData.rotation ? keyframeData.rotation[2] : ""
            }" onchange="updateKeyframe()"
            />
        </div>
        </div>`);
    }
    if (
      selectedObjectData.type != "camera" &&
      selectedObjectData.type != "light"
    ) {
      $("#objProperty #keyframeProps")
        .append(`<div class="col"><label>Scale</label>
        <div class="row frameScale" style="margin: 0">
        <input
        type="text"
        class="form-control col-sm-4"
        placeholder="X" value="${
          keyframeData.scale ? keyframeData.scale[0] : ""
        }" onchange="updateKeyframe()"
        />
        <input
        type="text"
        class="form-control col-sm-4"
        placeholder="Y" value="${
          keyframeData.scale ? keyframeData.scale[1] : ""
        }" onchange="updateKeyframe()"
        />
        <input
        type="text"
        class="form-control col-sm-4"
        placeholder="Z" value="${
          keyframeData.scale ? keyframeData.scale[2] : ""
        }" onchange="updateKeyframe()"
        />
        </div>
        </div>`);
    }
  } else {
    $("#objProperty #keyframeProps").css("visibility", "hidden");
  }
}

function selectKeyframe(element) {
  element = $(element);
  let frame = element.attr("frame");
  selectedKeyframe = frame;
  reloadProperties();
}

function addKeyframe() {
  let frame = prompt("Enter frame number");
  if (frame == null) {
    return;
  }
  let obj = animation.objects.find((o) => o.id === selectedObject);
  if (obj.keyframes[frame] != null) {
    alert("Keyframe already exists");
    return;
  }
  obj.keyframes[frame] = {
    position: null,
    rotation: null,
    scale: null,
  };
  reloadProperties();
}

function updateKeyframe() {
  let obj = animation.objects.find((o) => o.id === selectedObject);
  let keyframeData = obj.keyframes[selectedKeyframe];
  let position = [
    $("#objProperty #keyframeProps .position input[axis='X']").val(),
    $("#objProperty #keyframeProps .position input[axis='Y']").val(),
    $("#objProperty #keyframeProps .position input[axis='Z']").val(),
  ];
  let rotation = [
    $("#objProperty #keyframeProps .rotation input[axis='X']").val(),
    $("#objProperty #keyframeProps .rotation input[axis='Y']").val(),
    $("#objProperty #keyframeProps .rotation input[axis='Z']").val(),
  ];
  let scale = [
    $("#objProperty #keyframeProps .scale input[axis='X']").val(),
    $("#objProperty #keyframeProps .scale input[axis='Y']").val(),
    $("#objProperty #keyframeProps .scale input[axis='Z']").val(),
  ];
  if (position[0] || position[1] || position[2]) {
    keyframeData.position = position;
  } else {
    keyframeData.position = null;
  }
  if (rotation[0] || rotation[1] || rotation[2]) {
    keyframeData.rotation = rotation;
  } else {
    keyframeData.rotation = null;
  }
  if (scale[0] || scale[1] || scale[2]) {
    keyframeData.scale = scale;
  } else {
    keyframeData.scale = null;
  }
  reloadProperties();
  saveAnimation();
}

function updateLight() {
  let light = animation.objects.find((o) => o.id === selectedObject);
  let color = $("#objProperty #lightProps .lightColor input").val();
  color = hexToRgb(color);
  light.color = [color.r / 255, color.g / 255, color.b / 255];
  light.ambient = [
    $("#objProperty #lightProps .lightAmbient .x").val(),
    $("#objProperty #lightProps .lightAmbient .y").val(),
    $("#objProperty #lightProps .lightAmbient .z").val(),
  ];
  light.diffuse = [
    $("#objProperty #lightProps .lightDiffuse .x").val(),
    $("#objProperty #lightProps .lightDiffuse .y").val(),
    $("#objProperty #lightProps .lightDiffuse .z").val(),
  ];
  light.specular = [
    $("#objProperty #lightProps .lightSpecular .x").val(),
    $("#objProperty #lightProps .lightSpecular .y").val(),
    $("#objProperty #lightProps .lightSpecular .z").val(),
  ];
  reloadProperties();
  saveAnimation();
}

async function getDirectoryTree() {
  let files = {};
  for await (let entry of directoryHandle.values()) {
    if (entry.kind === "file" && !entry.name.startsWith(".")) {
      files[entry.name] = await(await entry.getFile()).text();
    }
  }
  return files;
}

async function preview() {
  let result = await axios.post('/api/preview', await getDirectoryTree());
  console.log(result);
}

async function render() {
  let result = await axios.post('/api/render', await getDirectoryTree());
  console.log(result);
}