/******/ (() => { // webpackBootstrap
/******/ 	"use strict";
/******/ 	var __webpack_modules__ = ({

/***/ "./src/blocks/block.js":
/*!*****************************!*\
  !*** ./src/blocks/block.js ***!
  \*****************************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

__webpack_require__.r(__webpack_exports__);
/* harmony export */ __webpack_require__.d(__webpack_exports__, {
/* harmony export */   wifi_button_ack: () => (/* binding */ wifi_button_ack),
/* harmony export */   wifi_button_command: () => (/* binding */ wifi_button_command),
/* harmony export */   wifi_button_set: () => (/* binding */ wifi_button_set),
/* harmony export */   wifi_client_init: () => (/* binding */ wifi_client_init),
/* harmony export */   wifi_data_read: () => (/* binding */ wifi_data_read),
/* harmony export */   wifi_data_send_ack: () => (/* binding */ wifi_data_send_ack),
/* harmony export */   wifi_init: () => (/* binding */ wifi_init),
/* harmony export */   wifi_read_ip: () => (/* binding */ wifi_read_ip),
/* harmony export */   wifi_read_sensor_set: () => (/* binding */ wifi_read_sensor_set)
/* harmony export */ });
/* harmony import */ var blockly_core__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! blockly/core */ "blockly/core");
/* harmony import */ var blockly_core__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(blockly_core__WEBPACK_IMPORTED_MODULE_0__);
/* eslint-disable func-style */
/* eslint-disable max-len */
/* eslint-disable require-jsdoc */


const WEB_COLOR = 120;

const wifi_init = {
    init: function () {
        this.setColour(WEB_COLOR);
        this.appendDummyInput("")
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.MIXLY_WIFI_INIT)
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldImage(__webpack_require__(/*! ../media/web.png */ "./src/media/web.png"), 52, 40));
        this.appendValueInput("SSID", String)
            .setCheck([String, Number])
            .setAlign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.ALIGN_RIGHT)
            .appendField("SSID")
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.MIXLY_WIFI_NAME);
        this.appendValueInput("PASSWD", String)
            .setCheck([String, Number])
            .setAlign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.ALIGN_RIGHT)
            .appendField("PASSWD")
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.MIXLY_WIFI_PASSWORD);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};


const wifi_read_ip = {
    init: function () {
        this.setColour(WEB_COLOR);
        this.appendDummyInput("")
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.MIXLY_WIFI_READ_IP)
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldImage(__webpack_require__(/*! ../media/web.png */ "./src/media/web.png"), 52, 40));
        this.setOutput(true, Number);
        this.setTooltip('');
    }
};

const wifi_client_init = {
    init: function () {
        this.setColour(WEB_COLOR);
        this.appendDummyInput("")
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.MIXLY_WIFI_CLIENT_INIT)
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldImage(__webpack_require__(/*! ../media/web.png */ "./src/media/web.png"), 52, 40));
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
        this.setTooltip('');
    }
};

const wifi_button_set = {
    "type": "wifi_button_set",
    "init": function () {
        this.setColour(WEB_COLOR);
        this.appendDummyInput("")
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.WIFI_BUTTON_SET)
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldImage(__webpack_require__(/*! ../media/web.png */ "./src/media/web.png"), 52, 40));
        this.appendDummyInput("")
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldDropdown([
                ['Red LED', '"Red LED", "RED_LED:1", "RED_LED:0"'],
                ['Green LED', '"Green LED", "GREEN_LED:1", "GREEN_LED:0"'],
                ['Blue LED', '"Blue LED", "BLUE_LED:1", "BLUE_LED:0"'],
                ['White LED', '"White LED", "WHITE_LED:1", "WHITE_LED:0"'],
                ['Relay', '"Relay", "RELAY:1", "RELAY:0"'],
                ['Laser', '"Laser", "LASER:1", "LASER:0"'],
                ['Water Pump', '"Water Pump", "PUMP:1", "PUMP:0"'],
                ['Servo', '"Servo", "SERVO:1", "SERVO:0"'],
                ['Motor', '"Motor", "MOTOR:1", "MOTOR:0"']
            ]), 'btn');
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
    }
};


const wifi_read_sensor_set = {
    "type": "wifi_read_sensor_set",
    "init": function () {
        this.setColour(WEB_COLOR);
        this.appendDummyInput("")
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.WIFI_READ_SENSOR_SET)
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldImage(__webpack_require__(/*! ../media/web.png */ "./src/media/web.png"), 52, 40));
        this.appendDummyInput("")
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldDropdown([
                ['Water Detect', '"Water Detect", "water", "waterValue"'],
                ['Temperature', '"Temperature(&deg;C)", "temperature", "tempValue"'],
                ['Humidity', '"Humidity(%RH)", "humidity", "humidityValue"'],
                ['Light', '"LIGHT", "light", "lightValue"'],
                ['Ultrasonic', '"Ultrasonic(cm)", "ultrasonic", "ultraValue"'],
                ['Smoke', '"Smoke", "smoke", "smokeValue"'],
                ['Alcohol', '"Alcohol", "alcohol", "alcoholValue"'],
                ['Soil Moisture', '"Soil Moisture", "soil", "soilValue"'],
                ['Pot', '"Pot", "pot", "potValue"'],
            ]), 'sensor');
        this.setInputsInline(true);
        this.setPreviousStatement(true, null);
        this.setNextStatement(true, null);
    }
};


const wifi_button_command = {
    init: function () {
        this.setColour(WEB_COLOR);
        this.appendDummyInput("")
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldImage(__webpack_require__(/*! ../media/web.png */ "./src/media/web.png"), 52, 40))
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.WIFI_BUTTON_COMMAND)
            // 下拉框改为二维数组格式
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldDropdown([
                ['RED LED', 'RED_LED'],
                ['GREEN LED', 'GREEN_LED'],
                ['BLUE LED', 'BLUE_LED'],
                ['WHITE LED', 'WHITE_LED'],
                ['RELAY', 'RELAY'],
                ['LASER', 'LASER'],
                ['PUMP', 'PUMP'],
                ['SERVO', 'SERVO'],
                ['MOTOR', 'MOTOR']
            ]), 'BUTTON_NAME')
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.WIFI_BUTTON_COMMAND_STATUS)
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldDropdown([
                ['ON', '1'],
                ['OFF', '0']
            ]), "STATUS");
        this.setOutput(true, String);
    }
};

const wifi_button_ack = {
    init: function () {
        this.setColour(WEB_COLOR);
        this.appendDummyInput("")
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldImage(__webpack_require__(/*! ../media/web.png */ "./src/media/web.png"), 52, 40))
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.WIFI_BUTTON_ACK)
            // 下拉框改为二维数组格式
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldDropdown([
                ['RED LED ON', 'ACK:RED_LED:1'],
                ['GREEN LED ON', 'ACK:GREEN_LED:1'],
                ['BLUE LED ON', 'ACK:BLUE_LED:1'],
                ['WHITE LED ON', 'ACK:WHITE_LED:1'],
                ['RELAY ON', 'ACK:RELAY:1'],
                ['LASER ON', 'ACK:LASER:1'],
                ['PUMP ON', 'ACK:PUMP:1'],
                ['SERVO ON', 'ACK:SERVO:1'],
                ['MOTOR ON', 'ACK:MOTOR:1'],
                ['RED LED OFF', 'ACK:RED_LED:0'],
                ['GREEN LED OFF', 'ACK:GREEN_LED:0'],
                ['BLUE LED OFF', 'ACK:BLUE_LED:0'],
                ['WHITE LED OFF', 'ACK:WHITE_LED:0'],
                ['RELAY OFF', 'ACK:RELAY:0'],
                ['LASER OFF', 'ACK:LASER:0'],
                ['PUMP OFF', 'ACK:PUMP:0'],
                ['SERVO OFF', 'ACK:SERVO:0'],
                ['MOTOR OFF', 'ACK:MOTOR:0']
            ]), 'BUTTON_NAME')
        this.setOutput(true, String);
    }
};

const wifi_data_read = {
    init: function () {
        this.setColour(WEB_COLOR);
        this.appendDummyInput("")
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldImage(__webpack_require__(/*! ../media/web.png */ "./src/media/web.png"), 52, 40))
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.SEND_SENOR_DATA)
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldDropdown([
                ['Water', 'WATER'],
                ['Temperature', 'TEMP'],
                ['Humidity', 'HUM'],
                ['Light', 'LIGHT'],
                ['Ultrasonic', 'ULTRA'],
                ['Smoke', 'SMOKE'],
                ['Alcohol', 'ALCOHOL'],
                ['Soil', 'SOIL'],
                ['Pot', 'POT'],
            ]), 'send_sensor_name');
        this.appendValueInput('value')
            .setCheck(Number)
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.SENSOR_Value);
        this.setInputsInline(true); // 横向排列（传感器类型+数值输入框在同一行）
        this.setOutput(true, String);
    }
};


const wifi_data_send_ack = {
    init: function () {
        this.setColour(WEB_COLOR);
        this.appendDummyInput("")
            .appendField(new blockly_core__WEBPACK_IMPORTED_MODULE_0__.FieldImage(__webpack_require__(/*! ../media/web.png */ "./src/media/web.png"), 52, 40))
            .appendField(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Msg.WIFI_DATA_SEND_ACK);
        this.setOutput(true, String);
        this.setTooltip('');
    }
};


/***/ }),

/***/ "./src/generators/generator.js":
/*!*************************************!*\
  !*** ./src/generators/generator.js ***!
  \*************************************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

__webpack_require__.r(__webpack_exports__);
/* harmony export */ __webpack_require__.d(__webpack_exports__, {
/* harmony export */   wifi_button_ack: () => (/* binding */ wifi_button_ack),
/* harmony export */   wifi_button_command: () => (/* binding */ wifi_button_command),
/* harmony export */   wifi_button_set: () => (/* binding */ wifi_button_set),
/* harmony export */   wifi_client_init: () => (/* binding */ wifi_client_init),
/* harmony export */   wifi_data_read: () => (/* binding */ wifi_data_read),
/* harmony export */   wifi_data_send_ack: () => (/* binding */ wifi_data_send_ack),
/* harmony export */   wifi_init: () => (/* binding */ wifi_init),
/* harmony export */   wifi_read_ip: () => (/* binding */ wifi_read_ip),
/* harmony export */   wifi_read_sensor_set: () => (/* binding */ wifi_read_sensor_set)
/* harmony export */ });
/* harmony import */ var blockly_core__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! blockly/core */ "blockly/core");
/* harmony import */ var blockly_core__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(blockly_core__WEBPACK_IMPORTED_MODULE_0__);
// 确保顶部已导入 Blockly


const wifi_init = function (block, generator) {
    var ssid = generator.valueToCode(block, "SSID", generator.ORDER_ATOMIC);
    var passwd = generator.valueToCode(block, "PASSWD", generator.ORDER_ATOMIC);
    // 头文件
    generator.definitions_["wifi_init"] =`#include <ESP8266WiFi.h>\n#include <WiFiClient.h>\n#include <ESP8266WebServer.h>\n#include <ArduinoJson.h>\nESP8266WebServer server(80);\n`;
    //wifi 名称与密码
    generator.definitions_["wifi_init2"] =
    "const char* ssid = " +
    ssid +
    ";\nconst char* password = " +
    passwd +
    ";\n";
    // 重发机制参数
    generator.definitions_["wifi_init3"] =
    "const int MAX_RETRY = 3;\nconst int RESPONSE_TIMEOUT = 500; // 0.5秒\n";

    // 传感器数据结构
    generator.definitions_["wifi_init4"] =
    "    struct ToggleButton {\n" +
    "   String btnName;    // 按钮显示文本\n" +
    "   String onCommand;  // 开启命令\n" +
    "   String offCommand; // 关闭命令\n" +
    "   String htmlId;     // 唯一ID\n" +
    "};\n" +
    "\n" +
    "struct SensorItem {\n" +
    "   String displayName; // 传感器显示名称\n" +
    "   String jsonKey;     // JSON字段名\n" +
    "   String htmlId;      // HTML元素ID\n" +
    "};\n" +
    "\n" +
    "ToggleButton buttons[15]; // 扩展容量（支持15个按键）\n" +
    "SensorItem sensors[15];   // 扩展容量（支持15个传感器）\n" +
    "int buttonCount = 0;\n" +
    "int sensorCount = 0;\n" +
    "\n" +
    "struct SensorData {\n" +
    "int water = 0;\n" +
    "    float temperature = 0;\n" +
    "    float humidity = 0;\n" +
    "    int light = 0;\n" +
    "    float ultrasonic = 0;\n" +
    "    int smoke = 0;\n" +
    "    int alcohol = 0;\n" +
    "    int soil = 0;\n" +
    "    int pot = 0;\n" +
    "};\n" +
    "\n" +
    "void addToggleButton(String btnName, String onCommand, String offCommand) {\n" +
    "   if (buttonCount < 15) {\n" +
    "       buttons[buttonCount].btnName = btnName;\n" +
    "       buttons[buttonCount].onCommand = onCommand;\n" +
    "       buttons[buttonCount].offCommand = offCommand;\n" +
    '       buttons[buttonCount].htmlId = "btn_" + String(buttonCount);\n' +
    "       buttonCount++;\n" +
    "   }\n" +
    "}\n" +
    "\n" +
    "void addSensor(String displayName, String jsonKey, String htmlId) {\n" +
    "   if (sensorCount < 15) {\n" +
    "       sensors[sensorCount].displayName = displayName;\n" +
    "       sensors[sensorCount].jsonKey = jsonKey;\n" +
    "       sensors[sensorCount].htmlId = htmlId;\n" +
    "       sensorCount++;\n" +
    "    }\n" +
    "}\n";

    generator.definitions_["wifi_init5"] =
    "SensorData sensorData;\nunsigned long lastSensorRead = 0;\nconst unsigned long SENSOR_READ_INTERVAL = 1000;\n  ";

    generator.definitions_["wifi_init6"] = "bool sendCommandWithRetry(String command) {\n" +
    "    for (int retry = 0; retry < MAX_RETRY; retry++) {\n" +
    "        Serial.println(command);\n" +
    "        unsigned long startTime = millis();\n" +
    "        while (millis() - startTime < RESPONSE_TIMEOUT) {\n" +
    "            if (Serial.available() > 0) {\n" +
    "                String response = Serial.readStringUntil('\\n');\n" +
    "                response.trim();\n" +
    "                // 如果收到任何有效响应（非空），就认为成功\n" +
    '                if (response.startsWith("ACK:")) {\n' +
    "                       String ackCommand = response.substring(4);\n" +
    "                       if (ackCommand == command) {\n" +
    '                           Serial.println("Received ACK for: " + command);\n' +
    "                           return true;  // 收到响应，认为成功\n" +
    "                       }\n" +
    "                   }\n" +
    "             }\n" +
    "            delay(10);\n" +
    "        }\n" +
    '        Serial.println("No ACK, retry " + String(retry + 1) + " for: " + command);\n' +
    "        delay(50);  // 短暂延迟后重试\n" +
    "    }\n" +
    '    Serial.println("Failed after " + String(MAX_RETRY) + " retries: " + command);\n' +
    "    return false;  // 重试次数用完\n" +
    "}\n";

    generator.setups_["wifi_setup"] =
    'WiFi.begin(ssid, password);\n  Serial.println("Connecting to WiFi");\n  while (WiFi.status() != WL_CONNECTED) {\n   delay(500);\n   Serial.print(".");\n}\n  Serial.println("");\n  Serial.println("WiFi connected");\n   Serial.print("IP address: ");\n   Serial.println(WiFi.localIP());\n   server.on("/", []() {server.send(200, "text/html", generateWebpage());});\n   server.on("/control", handleControl);\n   server.on("/read", handleReadSensors);\n   server.begin();\n   Serial.println("HTTP server started");\n';

    generator.definitions_["wifi_webpage"] =
    "String generateWebpage() {\n" +
    'String html = R"rawliteral(\n' +
    "<!DOCTYPE HTML>\n" +
    "<html>\n" +
    "<head>\n" +
    "<title>ESP8266 Control</title>\n" +
    '<meta name="viewport" content="width=device-width, initial-scale=1">\n' +
    "<style>\n" +
    "body {\n" +
    "font-family: Arial, sans-serif;\n" +
    "text-align: center;\n" +
    "max-width: 600px; /* 加宽页面，适配更多传感器 */\n" +
    "margin: 0 auto;\n" +
    "padding: 20px;\n" +
    "background-color: #f0f0f0;\n" +
    "}\n" +
    ".header {\n" +
    "margin-bottom: 30px;\n" +
    "color: #333;\n" +
    "}\n" +
    ".control-group {\n" +
    "margin-bottom: 30px;\n" +
    "display: flex;\n" +
    "flex-wrap: wrap;\n" +
    "justify-content: center;\n" +
    "gap: 15px;\n" +
    "}\n" +
    ".toggle-btn {\n" +
    "border: 2px solid #b0b0b0;\n" +
    "color: #333;\n" +
    "padding: 15px 25px;\n" +
    "text-align: center;\n" +
    "text-decoration: none;\n" +
    "font-size: 16px; /* 缩小字体，适配更多按键 */\n" +
    "cursor: pointer;\n" +
    "border-radius: 8px;\n" +
    "min-width: 120px; /* 缩小最小宽度，增加一行按键数量 */\n" +
    "transition: all 0.3s ease;\n" +
    "background-color: #e0e0e0;\n" +
    "box-sizing: border-box;\n" +
    "}\n" +
    ".toggle-btn.active {\n" +
    "border-color: #66BB6A;\n" +
    "background-color: #81C784;\n" +
    "color: #222;\n" +
    "}\n" +
    ".toggle-btn:active {\n" +
    "transform: scale(0.98);\n" +
    "border-color: #999;\n" +
    "}\n" +
    ".toggle-btn.active:active {\n" +
    "border-color: #4CAF50;\n" +
    "}\n" +
    ".status-message { \n" +
    "margin: 10px 0;\n" +
    "padding: 10px;\n" +
    "border-radius: 5px;\n" +
    "font-weight: bold;\n" +
    "}\n" +
    ".status-success {\n" +
    "background-color: #d4edda;\n" +
    "color: #155724;\n" +
    "border: 1px solid #c3e6cb;\n" +
    "}\n" +
    ".status-error {\n" +
    "background-color: #f8d7da;\n" +
    "color: #721c24;\n" +
    "border: 1px solid #f5c6cb;\n" +
    "}\n" +
    ".sensor-group {\n" +
    "margin: 30px 0;\n" +
    "display: grid;\n" +
    "grid-template-columns: 1fr 1fr; /* 传感器分2列显示，更紧凑 */\n" +
    "gap: 15px;\n" +
    "}\n" +
    ".sensor-value {\n" +
    "font-size: 18px; /* 缩小字体，适配2列布局 */\n" +
    "color: #2196F3;\n" +
    "margin: 10px 0;\n" +
    "font-weight: bold;\n" +
    "background-color: #fff; /* 传感器区域添加白色背景，增强区分 */\n" +
    "padding: 10px;\n" +
    "border-radius: 5px;\n" +
    "box-shadow: 0 2px 4px rgba(0,0,0,0.1);\n" +
    "}\n" +
    "</style>\n" +
    "</head>\n" +
    "<body>\n" +
    '<div class="header">\n' +
    "<h1>ESP8266 IoT Control</h1>\n" +
    '<div id="statusMessage" class="status-message"></div>\n' +
    "</div>\n" +
    "<!-- 动态生成的切换按键区域 -->\n" +
    '<div class="control-group">\n' +
    ')rawliteral";\n' +
    "\n" +
    "// 拼接所有按键（自动生成9个新增按键）\n" +
    "for (int i = 0; i < buttonCount; i++) {\n" +
    'html += "<button class=\\"toggle-btn\\" id=\\"" + buttons[i].htmlId + "\\" ";\n' +
    'html += "data-on-cmd=\\"" + buttons[i].onCommand + "\\" ";\n' +
    'html += "data-off-cmd=\\"" + buttons[i].offCommand + "\\" ";\n' +
    'html += "onclick=\\"sendCommandWithRetry(this)\\">";\n' +
    'html += buttons[i].btnName + "</button>";\n' +
    "}\n" +
    "\n" +
    'html += R"rawliteral(\n' +
    "</div>\n" +
    "\n" +
    "<!-- 动态生成的传感器显示区域（2列布局） -->\n" +
    '<div class="sensor-group">\n' +
    ')rawliteral";\n' +
    "\n" +
    "// 拼接所有传感器（自动生成8个新增传感器）\n" +
    "for (int i = 0; i < sensorCount; i++) {\n" +
    // 'html += "<div class=\"sensor-value\" id=\"" + sensors[i].htmlId + "\">" + sensors[i].displayName + ": ---</div>";\n' +
    'html += "<div class=\\"sensor-value\\" id=\\"" + sensors[i].htmlId + "\\">" + sensors[i].displayName + ": ---</div>";\n' +
    "}\n" +
    "\n" +
    'html += R"rawliteral(\n' +
    "</div>\n" +
    "\n" +
    "<script>\n" +
    "// 传感器配置（自动同步C++注册的传感器）\n" +
    "const sensors = [\n" +
    ')rawliteral";\n' +
    "\n" +
    "for (int i = 0; i < sensorCount; i++) {\n" +
    '  html += "{ jsonKey: \'" + sensors[i].jsonKey + "\', htmlId: \'" + sensors[i].htmlId + "\' }";\n' +
    '  if (i < sensorCount - 1) html += ",";\n' + // 处理数组逗号
    "};\n" +
    "\n" +
    'html += R"rawliteral(\n' +
    "];\n" +
    "\n" +
    "// 切换按键核心逻辑\n" +
    "function sendCommandWithRetry(btn) {\n" +
    'const onCmd = btn.getAttribute("data-on-cmd");\n' +
    'const offCmd = btn.getAttribute("data-off-cmd");\n' +
    'const isActive = btn.classList.contains("active");\n' +
    "\n" +
    "let command;\n" +
    "if (isActive) {\n" +
    "   command = offCmd;\n" +
    // "sendCommand(offCmd);\n" +
    // 'btn.classList.remove("active");\n' +
    "} else {\n" +
    "   command = onCmd;\n" +
    // "sendCommand(onCmd);\n" +
    // 'btn.classList.add("active");\n' +
    "}\n" +
    "showStatus(\"Sending: \" + command, \"info\");\n" +
    "\n" +
    "// 发送控制命令\n" +
    // "function sendCommand(command) {\n" +
    "var xhr = new XMLHttpRequest();\n" +
    'xhr.open("GET", "/control?cmd=" + encodeURIComponent(command), true);\n' +
    "xhr.onreadystatechange = function() { \n" +
        "if (xhr.readyState == 4) { \n" +
           "if (xhr.status == 200) {\n" +
                "var response = xhr.responseText;\n" +
                "if (response.includes(\"SUCCESS\")) {\n" +
                    "// 切换按钮状态\n" +
                    "if (isActive) {\n" +
                        "btn.classList.remove(\"active\");\n" +
                    "} else {\n" +
                        "btn.classList.add(\"active\");\n" +
                    "}\n" +
                    "showStatus(\"Success: \" + command, \"success\");\n" +
                "} else {\n" +
                    "showStatus(\"Failed: \" + command, \"error\");\n" +
                "}\n" +
            "} else {\n" +
                "showStatus(\"Network error\", \"error\");\n" +
            "}\n" +
        "}\n" +
    "};\n" +
    "xhr.send();\n" +
    "}\n" +
    "\n" +
    "function showStatus(message, type) {  \n" +
        "var statusDiv = document.getElementById(\"statusMessage\");\n" +
        "statusDiv.textContent = message;\n" +
        "statusDiv.className = \"status-message\";\n" +
        "\n" +
        "if (type === \"success\") {\n" +
            "statusDiv.classList.add(\"status-success\");\n" +
        "} else if (type === \"error\") {\n" +
            "statusDiv.classList.add(\"status-error\");\n" +
        "}\n" +
        "\n" +
        "// 3秒后清除状态消息\n" +
        "setTimeout(function() {\n" +
            "if (statusDiv.textContent === message) {\n" +
                "statusDiv.textContent = \"\";\n" +
                "statusDiv.className = \"status-message\";\n" +
            "}\n" +
        "}, 3000);\n" +
    "}\n" +
    "// 读取传感器数据（自动适配所有传感器）\n" +
    "function readSensors() {\n" +
    "var xhr = new XMLHttpRequest();\n" +
    'xhr.open("GET", "/read", true);\n' +
    "xhr.onreadystatechange = function() {\n" +
    "if (xhr.readyState == 4 && xhr.status == 200) {\n" +
    "try {\n" +
    "var data = JSON.parse(xhr.responseText);\n" +
    "sensors.forEach(sensor => {\n" +
    "if (data[sensor.jsonKey] !== undefined) {\n" +
    "// 保留传感器名称，仅更新数值\n" +
    'const label = document.getElementById(sensor.htmlId).innerText.split(":")[0];\n' +
    'document.getElementById(sensor.htmlId).innerHTML = label + ": " + data[sensor.jsonKey];\n' +
    "}\n" +
    "});\n" +
    "} catch(e) {\n" +
    'console.error("解析传感器数据失败:", e);\n' +
    "}\n" +
    "}\n" +
    "};\n" +
    "xhr.send();\n" +
    "}\n" +
    "\n" +
    "// 每1秒刷新传感器数据（提高刷新频率，更实时）\n" +
    "setInterval(readSensors, 1000);\n" +
    "window.onload = readSensors;\n" +
    "</script>\n" +
    "</body>\n" +
    "</html>\n" +
    ')rawliteral";\n' +
    "\n" +
    "return html;\n" +
    "}\n";

    generator.definitions_["wifi_read_serial_data1"] =
    "void readSensorData() {\n" +
    '  Serial.println("SENSOR_READ"); \n' +
    "  unsigned long startTime = millis();\n" +
    "  while (millis() - startTime < 500) { \n" +
    "    if (Serial.available() > 0) {\n" +
    "      String response = Serial.readStringUntil('\\n');\n" +
    "      response.trim();\n" +
    "\n" +
    "      // -------------------------- 解析传感器数据（按串口格式匹配） --------------------------\n" +
    "      // 假设传感器串口输出格式：WATER:1、TEMP:25.5、HUM:60.2、LIGHT:0、ULTRA:20.5、SMOKE:300、ALCOHOL:250、SOIL:500\n" +
    '      if (response.startsWith("WATER:")) sensorData.water = response.substring(6).toInt();\n' +
    '      else if (response.startsWith("TEMP:")) sensorData.temperature = response.substring(5).toFloat();\n' +
    '      else if (response.startsWith("HUM:")) sensorData.humidity = response.substring(4).toFloat();\n' +
    '      else if (response.startsWith("LIGHT:")) sensorData.light = response.substring(6).toInt();\n' +
    '      else if (response.startsWith("ULTRA:")) sensorData.ultrasonic = response.substring(6).toFloat();\n' +
    '      else if (response.startsWith("SMOKE:")) sensorData.smoke = response.substring(6).toInt();\n' +
    '      else if (response.startsWith("ALCOHOL:")) sensorData.alcohol = response.substring(8).toInt();\n' +
    '      else if (response.startsWith("SOIL:")) sensorData.soil = response.substring(5).toInt();\n' +
    '      else if (response.startsWith("POT:")) sensorData.pot = response.substring(4).toInt();\n' +
    "    }\n" +
    "    delay(10);\n" +
    "  }\n" +
    "}\n";

    // 生成 handleReadSensors 函数（处理传感器数据JSON响应）
    // 全局禁用该函数内的 no-useless-escape 规则（彻底解决转义报错）
    /* eslint-disable no-useless-escape */
    generator.definitions_["wifi_handle_read_sensors"] = `
    // 处理传感器数据读取请求，返回JSON格式响应
    void handleReadSensors() {
      String jsonResponse = "{";
      // eslint-disable-next-line no-undef -- sensors/i/sensorCount 是Arduino全局变量
      for (int i = 0; i < sensorCount; i++) {
        String jsonKey = sensors[i].jsonKey;
        // 匹配JSON字段与传感器数据（转义符确保Arduino生成正确JSON格式）
        if (jsonKey == "water") jsonResponse += "\\\"water\\":" + String(sensorData.water);
        else if (jsonKey == "temperature") jsonResponse += "\\\"temperature\\":" + String(sensorData.temperature, 1);
        else if (jsonKey == "humidity") jsonResponse += "\\\"humidity\\":" + String(sensorData.humidity, 1);
        else if (jsonKey == "light") jsonResponse += "\\\"light\\":" + String(sensorData.light);
        else if (jsonKey == "ultrasonic") jsonResponse += "\\\"ultrasonic\\":" + String(sensorData.ultrasonic, 1);
        else if (jsonKey == "smoke") jsonResponse += "\\\"smoke\\":" + String(sensorData.smoke);
        else if (jsonKey == "alcohol") jsonResponse += "\\\"alcohol\\":" + String(sensorData.alcohol);
        else if (jsonKey == "soil") jsonResponse += "\\\"soil\\":" + String(sensorData.soil);
        else if (jsonKey == "pot") jsonResponse += "\\\"pot\\":" + String(sensorData.pot);

        // 处理JSON数组逗号（最后一个元素后不加逗号）
        if (i < sensorCount - 1) jsonResponse += ",";
      }
      jsonResponse += "}";

      server.send(200, "application/json", jsonResponse);
    }
    `;

    generator.definitions_["wifi_data_send1"] =
    'void handleControl() {\n   if (server.hasArg("cmd")) {\n    String command = server.arg("cmd");\n    bool success = sendCommandWithRetry(command);\n    if (success) {\n     server.send(200, "text/plain", "SUCCESS: Command executed");\n    } else {\n     server.send(500, "text/plain", "ERROR: No response from UNO");\n    }\n   } else {\n    server.send(400, "text/plain", "Missing command");\n}\n}\n';


    return "server.handleClient();\n";
};

const wifi_read_ip = function (_, generator) {
    return [`WiFi.localIP()`, generator.ORDER_ATOMIC];
};

const wifi_client_init = function () {
    return "if (millis() - lastSensorRead >= SENSOR_READ_INTERVAL) {\n readSensorData();\n lastSensorRead = millis();\n}\n";
};

const wifi_button_set = function (block, generator) {
    // 1. 强制获取当前工作区（兼容所有米思齐版本）+ 忽略 Blockly 未定义报错
    const workspace =
    generator.workspace ||
    // eslint-disable-next-line no-undef -- Blockly 是米思齐全局变量
    blockly_core__WEBPACK_IMPORTED_MODULE_0__.getMainWorkspace();
    if (!workspace) {
        console.log("工作区未找到，返回空代码");
        return "// 按钮配置：工作区异常\n";
    }

    // 2. 强制获取当前积木参数（异常保护）
    const btnParams =
      block.getFieldValue("btn") || '"未知按钮", "UNKNOWN:1", "UNKNOWN:0"';
    // 保留 currentButtonCode 并强制使用
    const currentButtonCode = `addToggleButton(${btnParams});`;

    // 3. 强制收集代码（优先当前积木，再补充其他）
    const activeButtonCodes = [];
    // 第一步：强制添加当前积木代码（确保拖入就有代码）
    if (!activeButtonCodes.includes(currentButtonCode)) {
        activeButtonCodes.push(currentButtonCode);
    }

    // 第二步：补充其他按钮积木代码（支持多积木）
    const allBlocks = workspace.getAllBlocks();
    allBlocks.forEach((b) => {
        if (b.type === "wifi_button_set" && !b.isDisposed() && b.id !== block.id) {
            const blockParams =
            b.getFieldValue("btn") || '"未知按钮", "UNKNOWN:1", "UNKNOWN:0"';
            const code = `addToggleButton(${blockParams});`;
            if (!activeButtonCodes.includes(code)) {
                activeButtonCodes.push(code);
            }
        }
    });

    // 4. 标准化 setup() 代码格式（米思齐识别必成功）
    const setupCode = activeButtonCodes.join("\n  ");
    // 强制赋值到 setup()，米思齐会自动注入
    generator.setups_["wifi_button_setup"] = setupCode;
    console.log("生成的setup按钮代码：", setupCode); // 日志验证（按F12查看）

    // 5. 强制返回非空注释（米思齐代码区必显示）
    const buttonName = btnParams.split(",")[0].replace(/"/g, "") || "未知按钮";
    return `// 按钮配置：${buttonName}\n`;
};

const wifi_read_sensor_set = function (block, generator) {
    // 1. 兼容获取工作区（米思齐全局变量+ESLint 忽略）
    const workspace =
      generator.workspace ||
      // eslint-disable-next-line no-undef -- Blockly 是米思齐全局变量
      blockly_core__WEBPACK_IMPORTED_MODULE_0__.getMainWorkspace();
    if (!workspace) {
        console.log("传感器积木：工作区未找到");
        return "// 读取传感器数据：工作区异常\n";
    }

    // 2. 强制获取传感器参数（异常保护，避免空值）
    const sensorParams =
      block.getFieldValue("sensor") || '"未知传感器", "UNKNOWN_SENSOR"';
    // 保留核心变量：传感器代码（对应 addSensor 函数）
    const sensorCode = `addSensor(${sensorParams});`;

    // 3. 动态收集当前所有存在的传感器代码（去重+无残留）
    const activeSensorCodes = [];
    // 优先添加当前积木代码（拖入就生成）
    if (!activeSensorCodes.includes(sensorCode)) {
        activeSensorCodes.push(sensorCode);
    }

    // 补充其他传感器积木代码（支持多积木串联）
    const allBlocks = workspace.getAllBlocks();
    allBlocks.forEach((b) => {
        if (
            b.type === "wifi_read_sensor_set" &&
            !b.isDisposed() &&
            b.id !== block.id
        ) {
            const blockParams =
            b.getFieldValue("sensor") || '"未知传感器", "UNKNOWN_SENSOR"';
            const code = `addSensor(${blockParams});`;
            if (!activeSensorCodes.includes(code)) {
                activeSensorCodes.push(code);
            }
        }
    });

    // 4. 注入 setup()（单独键名，避免和按钮积木冲突！）
    const setupCode = activeSensorCodes.join("\n  ");
    generator.setups_["wifi_sensor_setup"] = setupCode;
    console.log("生成的传感器 setup 代码：", setupCode);

    // 5. 代码区显示注释（清晰标识传感器类型）
    const sensorName =
      sensorParams.split(",")[0].replace(/"/g, "") || "未知传感器";
    return `// 读取传感器数据：${sensorName}\n`;
};

const wifi_button_command = function (block) {
    // 获取两个下拉框的值
    const buttonName = block.getFieldValue("BUTTON_NAME");
    const status = block.getFieldValue("STATUS");
    // 拼接成完整命令（如 "RED_LED:1"），用引号包裹为字符串
    const command = `"${buttonName}:${status}"`;
    return [command, 0]; // 0 对应默认优先级，兼容米思齐生成器规则
};

const wifi_button_ack = function (block) {
    // 获取两个下拉框的值
    const buttonName = block.getFieldValue("BUTTON_NAME");
    
    // 拼接成完整命令（如 "RED_LED:1"），用引号包裹为字符串
    const command = `"${buttonName}"`;
    return [command, 0]; // 0 对应默认优先级，兼容米思齐生成器规则
};

// 实现模块化代码输出
const wifi_data_read = function (block, generator) {
    // 1. 获取传感器类型（如下拉框选择 Water，对应值 WATER）
    const sensorName = block.getFieldValue("send_sensor_name");
    // 2. 获取用户输入的数值（如 water 变量或具体数字）
    const valueCode = generator.valueToCode(
        block,
        "value",
        blockly_core__WEBPACK_IMPORTED_MODULE_0__.Arduino.ORDER_ATOMIC,
    );

    // 3. Arduino 代码：Serial.println("传感器类型:" + String(数值))
    const code = `"${sensorName}:" + String(${valueCode})\n`;

    return [code, 0];
};

const wifi_data_send_ack = function () {
    // 返回 "SENSOR_READ"（带引号，Arduino中是字符串常量）
    return [`"SENSOR_READ"`, blockly_core__WEBPACK_IMPORTED_MODULE_0__.Arduino.ORDER_ATOMIC];
};


/***/ }),

/***/ "./src/language/en.js":
/*!****************************!*\
  !*** ./src/language/en.js ***!
  \****************************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

__webpack_require__.r(__webpack_exports__);
/* harmony export */ __webpack_require__.d(__webpack_exports__, {
/* harmony export */   EnCatgories: () => (/* binding */ EnCatgories),
/* harmony export */   EnMsg: () => (/* binding */ EnMsg)
/* harmony export */ });
const EnMsg = {};

EnMsg.MIXLY_WIFI_INIT = 'WIFI Initialization';
EnMsg.MIXLY_WIFI_NAME = 'Name';
EnMsg.MIXLY_WIFI_PASSWORD = 'Password';
EnMsg.MIXLY_WIFI_READ_IP = 'WIFI Read IP';
EnMsg.MIXLY_WIFI_CLIENT_INIT = 'Read data command';
EnMsg.MIXLY_WIFI_CLIENT_CONNECTED = 'WIFI Client Not Connected';
EnMsg.MIXLY_WIFI_READ_DATA = 'WIFI Read Data';
EnMsg.MIXLY_WIFI_SEND_DATA = 'WIFI Send Data';

EnMsg.WIFI_DATA_SEND = 'WIFI sends data';
EnMsg.WIFI_DATA_READ = 'WIFI Read data';
// EnMsg.WIFI_READ_SERIAL_DATA = '读取串口数据';

EnMsg.WIFI_BUTTON_SET = 'Add Buttons';
EnMsg.WIFI_READ_SENSOR_SET = 'Read Sensor Data';

EnMsg.WIFI_BUTTON_COMMAND = 'Read Key';
EnMsg.WIFI_BUTTON_COMMAND_STATUS = 'Status';

EnMsg.WIFI_BUTTON_ACK = 'Key ACK';
EnMsg.WIFI_BUTTON_ACK_STATUS = 'Status';

EnMsg.SEND_SENOR_DATA = 'Send Data';
EnMsg.SENSOR_Value = 'Value';
EnMsg.WIFI_DATA_SEND_ACK = 'Confirm sending data';

const EnCatgories = {};

/***/ }),

/***/ "./src/language/zh-hans.js":
/*!*********************************!*\
  !*** ./src/language/zh-hans.js ***!
  \*********************************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

__webpack_require__.r(__webpack_exports__);
/* harmony export */ __webpack_require__.d(__webpack_exports__, {
/* harmony export */   ZhHansCatgories: () => (/* binding */ ZhHansCatgories),
/* harmony export */   ZhHansMsg: () => (/* binding */ ZhHansMsg)
/* harmony export */ });
const ZhHansMsg = {};

ZhHansMsg.MIXLY_WIFI_INIT = 'WIFI 初始化';
ZhHansMsg.MIXLY_WIFI_NAME = '名称';
ZhHansMsg.MIXLY_WIFI_PASSWORD = '密码';
ZhHansMsg.MIXLY_WIFI_READ_IP = 'WIFI 读取IP';
ZhHansMsg.MIXLY_WIFI_CLIENT_INIT = '读取数据指令';
ZhHansMsg.MIXLY_WIFI_CLIENT_COMMECTED = 'WIFI 没有连接客户端';
ZhHansMsg.MIXLY_WIFI_READ_DATA = 'WIFI 读取数据';
ZhHansMsg.MIXLY_WIFI_SEND_DATA = 'WIFI 发送数据';

ZhHansMsg.WIFI_DATA_SEND = 'WIFI 发送数据';
ZhHansMsg.WIFI_DATA_READ = 'WIFI 读取数据';
// ZhHansMsg.WIFI_READ_SERIAL_DATA = '读取串口数据';

ZhHansMsg.WIFI_BUTTON_SET = '添加控制按键';
ZhHansMsg.WIFI_READ_SENSOR_SET = '读取传感器数据';

ZhHansMsg.WIFI_BUTTON_COMMAND = '读取按键';
ZhHansMsg.WIFI_BUTTON_COMMAND_STATUS = '状态';

ZhHansMsg.WIFI_BUTTON_ACK = '按键应答';
ZhHansMsg.WIFI_BUTTON_ACK_STATUS = '状态';

ZhHansMsg.SEND_SENOR_DATA = '发送数据';
ZhHansMsg.SENSOR_Value = '值';
ZhHansMsg.WIFI_DATA_SEND_ACK = '确认发送数据';

const ZhHansCatgories = {};

/***/ }),

/***/ "./src/language/zh-hant.js":
/*!*********************************!*\
  !*** ./src/language/zh-hant.js ***!
  \*********************************/
/***/ ((__unused_webpack_module, __webpack_exports__, __webpack_require__) => {

__webpack_require__.r(__webpack_exports__);
/* harmony export */ __webpack_require__.d(__webpack_exports__, {
/* harmony export */   ZhHantCatgories: () => (/* binding */ ZhHantCatgories),
/* harmony export */   ZhHantMsg: () => (/* binding */ ZhHantMsg)
/* harmony export */ });
const ZhHantMsg = {};

ZhHantMsg.MIXLY_WIFI_INIT = 'WIFI 初始化';
ZhHantMsg.MIXLY_WIFI_NAME = '名稱';
ZhHantMsg.MIXLY_WIFI_PASSWORD = '密碼';
ZhHantMsg.MIXLY_WIFI_READ_IP = 'WIFI 讀取IP';
ZhHantMsg.MIXLY_WIFI_CLIENT_INIT = '讀取數據指令';
ZhHantMsg.MIXLY_WIFI_CLIENT_CONNECTED = 'WIFI 沒有連接客戶端'; 
ZhHantMsg.MIXLY_WIFI_READ_DATA = 'WIFI 讀取數據';
ZhHantMsg.MIXLY_WIFI_SEND_DATA = 'WIFI 發送數據';

ZhHantMsg.WIFI_DATA_SEND = 'WIFI 發送數據';
ZhHantMsg.WIFI_DATA_READ = 'WIFI 讀取數據';
// ZhHantMsg.WIFI_READ_SERIAL_DATA = '读取串口数据';
ZhHantMsg.WIFI_BUTTON_SET = '添加控制按鍵';
ZhHantMsg.WIFI_READ_SENSOR_SET = '讀取感測器數據';

ZhHantMsg.WIFI_BUTTON_COMMAND = '讀取按鍵';
ZhHantMsg.WIFI_BUTTON_COMMAND_STATUS = '狀態';

ZhHantMsg.WIFI_BUTTON_ACK = '按鍵應答';
ZhHantMsg.WIFI_BUTTON_ACK_STATUS = '狀態';

ZhHantMsg.SEND_SENOR_DATA = '發送數據';
ZhHantMsg.SENSOR_Value = '值';

ZhHantMsg.WIFI_DATA_SEND_ACK = '確認發送數據';

const ZhHantCatgories = {};

/***/ }),

/***/ "./src/media/web.png":
/*!***************************!*\
  !*** ./src/media/web.png ***!
  \***************************/
/***/ ((module) => {

module.exports = "data:image/png;base64,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";

/***/ }),

/***/ "blockly/core":
/*!**************************!*\
  !*** external "Blockly" ***!
  \**************************/
/***/ ((module) => {

module.exports = Blockly;

/***/ })

/******/ 	});
/************************************************************************/
/******/ 	// The module cache
/******/ 	var __webpack_module_cache__ = {};
/******/ 	
/******/ 	// The require function
/******/ 	function __webpack_require__(moduleId) {
/******/ 		// Check if module is in cache
/******/ 		var cachedModule = __webpack_module_cache__[moduleId];
/******/ 		if (cachedModule !== undefined) {
/******/ 			return cachedModule.exports;
/******/ 		}
/******/ 		// Create a new module (and put it into the cache)
/******/ 		var module = __webpack_module_cache__[moduleId] = {
/******/ 			// no module.id needed
/******/ 			// no module.loaded needed
/******/ 			exports: {}
/******/ 		};
/******/ 	
/******/ 		// Execute the module function
/******/ 		__webpack_modules__[moduleId](module, module.exports, __webpack_require__);
/******/ 	
/******/ 		// Return the exports of the module
/******/ 		return module.exports;
/******/ 	}
/******/ 	
/************************************************************************/
/******/ 	/* webpack/runtime/compat get default export */
/******/ 	(() => {
/******/ 		// getDefaultExport function for compatibility with non-harmony modules
/******/ 		__webpack_require__.n = (module) => {
/******/ 			var getter = module && module.__esModule ?
/******/ 				() => (module['default']) :
/******/ 				() => (module);
/******/ 			__webpack_require__.d(getter, { a: getter });
/******/ 			return getter;
/******/ 		};
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/define property getters */
/******/ 	(() => {
/******/ 		// define getter functions for harmony exports
/******/ 		__webpack_require__.d = (exports, definition) => {
/******/ 			for(var key in definition) {
/******/ 				if(__webpack_require__.o(definition, key) && !__webpack_require__.o(exports, key)) {
/******/ 					Object.defineProperty(exports, key, { enumerable: true, get: definition[key] });
/******/ 				}
/******/ 			}
/******/ 		};
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/hasOwnProperty shorthand */
/******/ 	(() => {
/******/ 		__webpack_require__.o = (obj, prop) => (Object.prototype.hasOwnProperty.call(obj, prop))
/******/ 	})();
/******/ 	
/******/ 	/* webpack/runtime/make namespace object */
/******/ 	(() => {
/******/ 		// define __esModule on exports
/******/ 		__webpack_require__.r = (exports) => {
/******/ 			if(typeof Symbol !== 'undefined' && Symbol.toStringTag) {
/******/ 				Object.defineProperty(exports, Symbol.toStringTag, { value: 'Module' });
/******/ 			}
/******/ 			Object.defineProperty(exports, '__esModule', { value: true });
/******/ 		};
/******/ 	})();
/******/ 	
/************************************************************************/
var __webpack_exports__ = {};
// This entry needs to be wrapped in an IIFE because it needs to be isolated against other modules in the chunk.
(() => {
/*!**********************!*\
  !*** ./src/index.js ***!
  \**********************/
__webpack_require__.r(__webpack_exports__);
/* harmony import */ var blockly_core__WEBPACK_IMPORTED_MODULE_0__ = __webpack_require__(/*! blockly/core */ "blockly/core");
/* harmony import */ var blockly_core__WEBPACK_IMPORTED_MODULE_0___default = /*#__PURE__*/__webpack_require__.n(blockly_core__WEBPACK_IMPORTED_MODULE_0__);
/* harmony import */ var _language_zh_hans__WEBPACK_IMPORTED_MODULE_1__ = __webpack_require__(/*! ./language/zh-hans */ "./src/language/zh-hans.js");
/* harmony import */ var _language_zh_hant__WEBPACK_IMPORTED_MODULE_2__ = __webpack_require__(/*! ./language/zh-hant */ "./src/language/zh-hant.js");
/* harmony import */ var _language_en__WEBPACK_IMPORTED_MODULE_3__ = __webpack_require__(/*! ./language/en */ "./src/language/en.js");
/* harmony import */ var _generators_generator__WEBPACK_IMPORTED_MODULE_4__ = __webpack_require__(/*! ./generators/generator */ "./src/generators/generator.js");
/* harmony import */ var _blocks_block__WEBPACK_IMPORTED_MODULE_5__ = __webpack_require__(/*! ./blocks/block */ "./src/blocks/block.js");







// 载入语言文件
Object.assign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Lang.ZhHans, _language_zh_hans__WEBPACK_IMPORTED_MODULE_1__.ZhHansMsg);
Object.assign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Lang.ZhHant, _language_zh_hant__WEBPACK_IMPORTED_MODULE_2__.ZhHantMsg);
Object.assign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Lang.En, _language_en__WEBPACK_IMPORTED_MODULE_3__.EnMsg);
Object.assign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Lang.ZhHans.MSG, _language_zh_hans__WEBPACK_IMPORTED_MODULE_1__.ZhHansCatgories);
Object.assign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Lang.ZhHant.MSG, _language_zh_hant__WEBPACK_IMPORTED_MODULE_2__.ZhHantCatgories);
Object.assign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Lang.En.MSG, _language_en__WEBPACK_IMPORTED_MODULE_3__.EnCatgories);

// 载入图形化模块外观定义文件
Object.assign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Blocks, _blocks_block__WEBPACK_IMPORTED_MODULE_5__);

// 载入图形化模块代码生成定义文件
Object.assign(blockly_core__WEBPACK_IMPORTED_MODULE_0__.Arduino.forBlock, _generators_generator__WEBPACK_IMPORTED_MODULE_4__);
})();

/******/ })()
;
//# sourceMappingURL=main.bundle.js.map