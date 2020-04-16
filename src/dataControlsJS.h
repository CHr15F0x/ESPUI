const char JS_CONTROLS[] PROGMEM = R"=====(
const UI_INITIAL_GUI=200;const UPDATE_OFFSET=100;const UI_TITEL=0;const UI_PAD=1;const UPDATE_PAD=101;const UI_CPAD=2;const UPDATE_CPAD=102;const UI_BUTTON=3;const UPDATE_BUTTON=103;const UI_LABEL=4;const UPDATE_LABEL=104;const UI_SWITCHER=5;const UPDATE_SWITCHER=105;const UI_SLIDER=6;const UPDATE_SLIDER=106;const UI_NUMBER=7;const UPDATE_NUMBER=107;const UI_TEXT_INPUT=8;const UPDATE_TEXT_INPUT=108;const UI_GRAPH=9;const ADD_GRAPH_POINT=10;const CLEAR_GRAPH=109;const UI_TAB=11;const UPDATE_TAB=111;const UI_SELECT=12;const UPDATE_SELECT=112;const UI_OPTION=13;const UPDATE_OPTION=113;const UI_MIN=14;const UPDATE_MIN=114;const UI_MAX=15;const UPDATE_MAX=115;const UI_STEP=16;const UPDATE_STEP=116;const UI_GAUGE=17;const UPTDATE_GAUGE=117;const UI_ACCEL=18;const UPTDATE_ACCEL=117;const UP=0;const DOWN=1;const LEFT=2;const RIGHT=3;const CENTER=4;const C_TURQUOISE=0;const C_EMERALD=1;const C_PETERRIVER=2;const C_WETASPHALT=3;const C_SUNFLOWER=4;const C_CARROT=5;const C_ALIZARIN=6;const C_DARK=7;const C_NONE=255;var graphData=new Array();var hasAccel=false;var sliderContinuous=false;function colorClass(colorId){colorId=Number(colorId);switch(colorId){case C_TURQUOISE:return"turquoise";case C_EMERALD:return"emerald";case C_PETERRIVER:return"peterriver";case C_WETASPHALT:return"wetasphalt";case C_SUNFLOWER:return"sunflower";case C_CARROT:return"carrot";case C_ALIZARIN:return"alizarin";case C_NONE:return"dark";default:return"";}}
var websock;var websockConnected=false;function requestOrientationPermission(){}
function saveGraphData(){localStorage.setItem("espuigraphs",JSON.stringify(graphData));}
function restoreGraphData(id){var savedData=localStorage.getItem("espuigraphs",graphData);if(savedData!=null){savedData=JSON.parse(savedData);return savedData[id];}
return[];}
function restart(){$(document).add("*").off();$("#row").html("");websock.close();start();}
function conStatusError(){websockConnected=false;$("#conStatus").removeClass("color-green");$("#conStatus").addClass("color-red");$("#conStatus").html("Error / No Connection &#8635;");$("#conStatus").off();$("#conStatus").on({click:restart});}
function handleVisibilityChange(){if(!websockConnected&&!document.hidden){restart();}}
function start(){document.addEventListener("visibilitychange",handleVisibilityChange,false);if(window.location.port!=""||window.location.port!=80||window.location.port!=443){websock=new WebSocket("ws://"+window.location.hostname+":"+window.location.port+"/ws");}else{websock=new WebSocket("ws://"+window.location.hostname+"/ws");}
websock.onopen=function(evt){console.log("websock open");$("#conStatus").addClass("color-green");$("#conStatus").text("Connected");websockConnected=true;};websock.onclose=function(evt){console.log("websock close");conStatusError();};websock.onerror=function(evt){console.log(evt);conStatusError();};var handleEvent=function(evt){var data=JSON.parse(evt.data);var e=document.body;var center="";switch(data.type){case UI_INITIAL_GUI:if(data.sliderContinuous){sliderContinuous=data.sliderContinuous;}
data.controls.forEach(element=>{var fauxEvent={data:JSON.stringify(element)};handleEvent(fauxEvent);});break;case UI_TITEL:document.title=data.label;$("#mainHeader").html(data.label);break;case UI_LABEL:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<span id='l"+
data.id+
"' class='label label-wrap'>"+
data.value+
"</span>"+
"</div>");break;case UI_BUTTON:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='one columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<button id='btn"+
data.id+
"' "+
"onmousedown='buttonclick("+
data.id+
", true)' "+
"onmouseup='buttonclick("+
data.id+
", false)'>"+
data.value+
"</button></div>");$("#btn"+data.id).on({touchstart:function(e){e.preventDefault();buttonclick(data.id,true);},touchend:function(e){e.preventDefault();buttonclick(data.id,false);}});break;case UI_SWITCHER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='one columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<label id='sl"+
data.id+
"' class='switch "+
(data.value=="1"?"checked":"")+
"'>"+
"<div class='in'><input type='checkbox' id='s"+
data.id+
"' onClick='switcher("+
data.id+
",null)' "+
(data.value=="1"?"checked":"")+
"/></div>"+
"</label>"+
"</div>");switcher(data.id,data.value);break;case UI_CPAD:case UI_PAD:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<nav class='control'>"+
"<ul>"+
"<li><a onmousedown='padclick(UP, "+
data.id+
", true)' onmouseup='padclick(UP, "+
data.id+
", false)' id='pf"+
data.id+
"'>▲</a></li>"+
"<li><a onmousedown='padclick(RIGHT, "+
data.id+
", true)' onmouseup='padclick(RIGHT, "+
data.id+
", false)' id='pr"+
data.id+
"'>▲</a></li>"+
"<li><a onmousedown='padclick(LEFT, "+
data.id+
", true)' onmouseup='padclick(LEFT, "+
data.id+
", false)' id='pl"+
data.id+
"'>▲</a></li>"+
"<li><a onmousedown='padclick(DOWN, "+
data.id+
", true)' onmouseup='padclick(DOWN, "+
data.id+
", false)' id='pb"+
data.id+
"'>▲</a></li>"+
"</ul>"+
(data.type==UI_CPAD?"<a class='confirm' onmousedown='padclick(CENTER,"+
data.id+
", true)' onmouseup='padclick(CENTER, "+
data.id+
", false)' id='pc"+
data.id+
"'>OK</a>":"")+
"</nav>"+
"</div>");$("#pf"+data.id).on({touchstart:function(e){e.preventDefault();padclick(UP,data.id,true);},touchend:function(e){e.preventDefault();padclick(UP,data.id,false);}});$("#pl"+data.id).on({touchstart:function(e){e.preventDefault();padclick(LEFT,data.id,true);},touchend:function(e){e.preventDefault();padclick(LEFT,data.id,false);}});$("#pr"+data.id).on({touchstart:function(e){e.preventDefault();padclick(RIGHT,data.id,true);},touchend:function(e){e.preventDefault();padclick(RIGHT,data.id,false);}});$("#pb"+data.id).on({touchstart:function(e){e.preventDefault();padclick(DOWN,data.id,true);},touchend:function(e){e.preventDefault();padclick(DOWN,data.id,false);}});$("#pc"+data.id).on({touchstart:function(e){e.preventDefault();padclick(CENTER,data.id,true);},touchend:function(e){e.preventDefault();padclick(CENTER,data.id,false);}});break;case UI_SLIDER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='two columns card tcenter card-slider "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<div class='range-slider'>"+
"<input id='sl"+
data.id+
"' type='range' min='0' max='100' value='"+
data.value+
"' class='range-slider__range'>"+
"<span class='range-slider__value'>"+
data.value+
"</span>"+
"</div>"+
"</div>");rangeSlider(!sliderContinuous);break;case UI_NUMBER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<input style='color:black;' id='num"+
data.id+
"' type='number' value='"+
data.value+
"' onchange='numberchange("+
data.id+
")' />"+
"</div>");break;case UI_TEXT_INPUT:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<input style='color:black;' id='text"+
data.id+
"' value='"+
data.value+
"' onchange='textchange("+
data.id+
")' />"+
"</div>");if(!data.visible){$("#id"+data.id).hide();}
break;case UI_TAB:$("#tabsnav").append("<li><a href='#tab"+data.id+"'>"+data.value+"</a></li>");$("#tabscontent").append("<div id='tab"+data.id+"'></div>");tabs=$(".tabscontent").tabbedContent({loop:true}).data("api");$("a").filter(function(){return $(this).attr("href")==="#click-to-switch";}).on("click",function(e){var tab=prompt("Tab to switch to (number or id)?");if(!tabs.switchTab(tab)){alert("That tab does not exist :\\");}
e.preventDefault();});break;case UI_SELECT:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<select style='color:black;' id='select"+
data.id+
"' onchange='selectchange("+
data.id+
")' />"+
"</div>");break;case UI_OPTION:if(data.parentControl){var parent=$("#select"+data.parentControl);parent.append("<option id='option"+
data.id+
"' value='"+
data.value+
"' "+
data.selected+
">"+
data.label+
"</option>");}
break;case UI_MIN:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){parent.attr("min",data.value);}}
break;case UI_MAX:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){parent.attr("max",data.value);}}
break;case UI_STEP:if(data.parentControl){var parent=$("#id"+data.parentControl+" input");if(parent.size()){parent.attr("step",data.value);}}
break;case UI_GRAPH:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"<figure id='graph"+
data.id+
"'>"+
"<figcaption>"+
data.label+
"</figcaption>"+
"</figure>"+
"</div>");graphData[data.id]=restoreGraphData(data.id);renderGraphSvg(graphData[data.id],"graph"+data.id);break;case ADD_GRAPH_POINT:var ts=Math.round(new Date().getTime()/1000);graphData[data.id].push({x:ts,y:data.value});saveGraphData();renderGraphSvg(graphData[data.id],"graph"+data.id);break;case CLEAR_GRAPH:graphData[data.id]=[];saveGraphData();renderGraphSvg(graphData[data.id],"graph"+data.id);break;case UI_GAUGE:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
parent.append("<div id='id"+
data.id+
"' class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"WILL BE A GAUGE <input style='color:black;' id='gauge"+
data.id+
"' type='number' value='"+
data.value+
"' onchange='numberchange("+
data.id+
")' />"+
"</div>");break;case UI_ACCEL:if(hasAccel)break;var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
hasAccel=true;parent.append("<div id='id"+
data.id+
"' class='two columns card tcenter "+
colorClass(data.color)+
"'>"+
"<h5>"+
data.label+
"</h5><hr/>"+
"ACCEL // Not implemented fully!<div class='accelerometer' id='accel"+
data.id+
"' ><div class='ball"+
data.id+
"'></div><pre class='accelerometeroutput"+
data.id+
"'></pre>"+
"</div>");requestOrientationPermission();break;case UPDATE_LABEL:$("#l"+data.id).html(data.value);break;case UPDATE_SWITCHER:switcher(data.id,data.value=="0"?0:1);break;case UPDATE_SLIDER:slider_move($("#sl"+data.id),data.value,"100",false);break;case UPDATE_NUMBER:$("#num"+data.id).val(data.value);break;case UPDATE_TEXT_INPUT:if(data.visible){$("#text"+data.id).val(data.value);$("#id"+data.id).show();}else{$("#id"+data.id).hide();}
break;case UPDATE_SELECT:$("#select"+data.id).val(data.value);break;case UPDATE_BUTTON:case UPDATE_PAD:case UPDATE_CPAD:break;case UPDATE_GAUGE:$("#gauge"+data.id).val(data.value);break;case UPDATE_ACCEL:break;default:console.error("Unknown type or event");break;}
if(data.type>=UPDATE_OFFSET&&data.type<UI_INITIAL_GUI){var element=$("#id"+data.id);if(data.type==UPDATE_SLIDER){element.removeClass("slider-turquoise slider-emerald slider-peterriver slider-wetasphalt slider-sunflower slider-carrot slider-alizarin");element.addClass("slider-"+colorClass(data.color));}else{element.removeClass("turquoise emerald peterriver wetasphalt sunflower carrot alizarin");element.addClass(colorClass(data.color));}}};websock.onmessage=handleEvent;}
function sliderchange(number){var val=$("#sl"+number).val();websock.send("slvalue:"+val+":"+number);}
function numberchange(number){var val=$("#num"+number).val();websock.send("nvalue:"+val+":"+number);}
function textchange(number){var val=$("#text"+number).val();websock.send("tvalue:"+val+":"+number);}
function selectchange(number){var val=$("#select"+number).val();websock.send("svalue:"+val+":"+number);}
function buttonclick(number,isdown){if(isdown)websock.send("bdown:"+number);else websock.send("bup:"+number);}
function padclick(type,number,isdown){switch(type){case CENTER:if(isdown)websock.send("pcdown:"+number);else websock.send("pcup:"+number);break;case UP:if(isdown)websock.send("pfdown:"+number);else websock.send("pfup:"+number);break;case DOWN:if(isdown)websock.send("pbdown:"+number);else websock.send("pbup:"+number);break;case LEFT:if(isdown)websock.send("pldown:"+number);else websock.send("plup:"+number);break;case RIGHT:if(isdown)websock.send("prdown:"+number);else websock.send("prup:"+number);break;}}
function switcher(number,state){if(state==null){if($("#s"+number).is(":checked")){websock.send("sactive:"+number);$("#sl"+number).addClass("checked");}else{websock.send("sinactive:"+number);$("#sl"+number).removeClass("checked");}}else if(state==1){$("#sl"+number).addClass("checked");$("#sl"+number).prop("checked",true);}else if(state==0){$("#sl"+number).removeClass("checked");$("#sl"+number).prop("checked",false);}}
var rangeSlider=function(isDiscrete){var slider=$(".range-slider"),range=$(".range-slider__range"),value=$(".range-slider__value");slider.each(function(){value.each(function(){var value=$(this).prev().attr("value");$(this).html(value);});if(!isDiscrete){range.on({input:function(){sliderchange($(this).attr("id").replace(/^\D+/g,""));}});}else{range.on({input:function(){$(this).next().html(this.value);},change:function(){sliderchange($(this).attr("id").replace(/^\D+/g,""));}});}});};
)=====";

const uint8_t JS_CONTROLS_GZIP[3352] PROGMEM = { 31,139,8,0,3,207,152,94,2,255,237,90,235,118,218,72,18,254,159,167,80,148,57,65,90,99,46,185,77,6,44,231,16,76,18,118,136,237,181,241,100,206,38,89,78,131,26,163,19,33,105,90,45,99,15,195,107,236,131,236,35,237,147,108,245,77,106,9,129,73,156,153,157,61,217,31,113,80,117,245,87,213,85,213,213,183,154,132,65,76,141,139,254,168,127,220,31,246,59,131,209,235,139,190,243,168,209,104,79,68,195,233,81,103,216,27,157,188,122,117,222,27,58,205,140,222,31,13,251,195,222,192,209,8,167,157,35,167,153,239,199,73,141,102,198,211,101,148,71,121,166,174,224,122,148,113,189,188,24,14,79,142,157,199,121,62,73,109,54,30,103,156,131,206,75,80,226,73,158,81,16,155,141,39,25,223,249,187,254,176,251,166,119,230,60,205,179,166,244,102,227,169,198,61,232,31,1,237,89,129,87,80,155,141,103,25,231,241,197,219,151,64,251,62,207,41,169,205,198,247,154,185,122,63,15,193,200,167,23,67,231,121,158,91,107,105,54,158,103,61,94,159,117,78,223,56,63,72,66,231,232,72,80,70,167,39,253,99,198,42,27,186,131,94,231,76,50,55,27,63,104,18,59,47,157,102,193,33,130,166,57,228,188,55,232,117,1,173,224,19,69,110,106,94,57,57,29,246,153,253,11,110,81,228,166,230,150,183,125,32,20,188,194,105,77,205,39,111,59,63,59,205,130,63,56,173,169,187,98,216,59,117,154,69,79,112,98,83,243,195,235,206,197,235,158,211,204,252,48,228,140,146,220,212,252,208,233,118,89,112,60,47,112,74,178,134,144,134,246,209,201,187,227,52,176,7,189,87,195,52,128,207,250,175,223,12,211,48,237,246,142,135,224,117,53,194,238,104,120,113,246,183,139,147,254,121,47,133,234,142,122,111,123,103,157,65,54,81,186,163,211,30,244,58,235,255,4,93,31,165,196,119,189,97,231,252,244,77,103,160,193,143,206,47,142,95,13,78,222,229,100,116,59,103,103,39,195,52,172,187,163,206,160,255,247,206,25,216,250,89,74,58,234,156,253,152,134,104,119,116,124,114,220,115,30,61,125,218,190,66,196,184,36,40,154,29,33,138,156,0,47,140,14,33,232,198,178,121,203,12,197,157,201,4,251,206,20,249,49,230,164,216,247,92,76,186,97,64,189,32,9,147,88,54,77,147,96,66,189,48,48,38,161,31,146,174,143,226,216,226,63,251,174,189,148,63,156,227,100,62,198,36,165,183,227,133,71,39,51,141,15,197,88,183,89,139,96,154,144,192,132,63,191,36,161,23,99,179,45,89,164,9,21,3,158,99,130,124,55,109,206,236,169,56,34,76,49,33,222,21,38,41,83,102,95,197,180,192,20,197,209,12,249,52,101,74,237,173,120,226,36,152,250,225,66,195,17,230,87,237,19,68,72,152,245,87,174,80,205,200,247,126,69,196,11,82,6,230,9,213,232,34,242,201,108,187,120,138,18,159,42,162,217,94,173,238,49,203,47,240,56,14,39,159,218,218,111,112,67,128,39,20,187,69,47,16,252,75,130,99,122,66,60,28,80,196,72,167,152,204,189,56,134,95,150,189,92,221,75,57,99,116,133,95,171,0,128,38,63,156,32,255,156,134,4,93,226,90,140,105,159,226,185,101,226,56,74,60,30,39,177,89,253,235,249,201,113,45,166,48,138,75,111,122,99,165,225,99,219,109,13,152,128,252,144,104,216,30,120,152,71,16,72,116,121,184,229,100,93,150,202,202,192,219,222,212,74,187,222,119,130,196,247,237,101,134,197,149,138,16,137,113,198,101,183,133,13,51,145,239,61,247,35,40,41,200,239,63,22,245,69,132,130,9,190,179,220,112,146,204,193,114,118,13,185,174,101,254,197,180,107,225,116,10,147,226,59,203,124,64,194,5,124,207,232,220,183,76,211,110,75,87,212,38,126,8,178,33,168,5,138,14,13,179,238,28,188,144,196,61,136,13,2,18,54,184,143,161,167,188,32,131,224,121,120,133,197,100,50,249,44,217,191,36,24,7,166,189,198,10,122,230,248,8,118,75,184,132,210,92,11,163,110,28,135,134,212,128,41,249,240,193,243,103,143,159,182,75,122,101,67,207,81,3,107,57,241,189,201,167,150,180,220,42,55,230,25,10,92,31,255,228,197,222,216,243,61,122,211,5,194,37,216,103,9,110,188,95,28,255,195,135,247,149,201,107,51,207,117,113,96,47,83,127,176,248,207,194,85,250,40,101,135,129,247,174,224,199,192,139,41,14,32,187,152,87,169,204,9,151,105,86,203,117,169,114,163,243,184,90,120,129,27,46,106,44,30,153,148,90,20,18,122,223,49,205,223,126,43,111,121,222,216,212,242,228,201,227,212,189,60,157,190,195,227,115,248,141,169,101,46,226,86,189,110,238,21,59,206,194,152,6,104,142,247,204,214,122,35,67,221,51,235,11,176,120,123,133,65,223,47,6,151,24,247,84,188,134,65,24,225,192,81,150,181,240,21,101,153,58,136,67,31,67,255,75,128,20,156,6,227,219,33,228,54,133,38,197,215,160,95,234,235,108,202,100,225,79,73,130,219,171,118,166,26,159,76,187,232,198,25,1,178,56,197,114,104,152,209,182,160,49,66,25,130,88,2,89,236,240,16,43,32,176,86,183,144,122,160,161,230,242,204,195,90,177,147,134,233,56,116,111,56,109,2,95,152,64,108,169,213,143,177,215,232,77,132,229,250,151,223,135,183,32,58,57,71,113,221,133,220,87,92,137,75,249,192,227,156,14,195,163,36,244,227,218,52,36,61,4,114,177,143,153,102,206,33,31,8,44,57,215,98,144,75,198,222,42,228,120,201,108,175,218,154,61,172,180,19,24,203,110,143,9,70,159,218,106,12,252,104,208,74,199,79,61,234,99,161,161,143,198,216,231,81,50,71,94,240,6,35,208,87,229,166,140,161,136,199,55,244,45,166,42,88,26,16,219,202,48,226,179,43,134,103,47,197,167,195,224,41,26,155,123,37,60,114,34,105,156,60,165,131,165,4,169,134,34,136,120,200,251,7,174,119,101,120,174,83,241,92,115,79,152,209,115,247,238,153,21,8,59,8,124,167,66,23,33,219,240,36,243,32,54,96,225,119,13,42,220,107,0,187,182,17,146,14,128,111,155,245,62,132,86,243,96,246,244,80,129,242,1,51,90,29,136,7,51,82,23,28,113,132,2,46,222,47,151,206,187,25,252,239,254,2,214,201,74,10,120,133,252,4,115,64,134,33,208,234,48,152,67,179,104,86,113,160,250,179,217,21,166,236,239,104,215,113,66,105,40,44,59,166,65,65,3,198,17,6,115,152,57,24,18,105,0,44,156,155,175,116,86,142,183,106,176,180,101,231,186,36,209,214,14,98,197,41,243,147,232,116,152,122,137,89,143,43,39,187,139,245,150,134,201,100,198,151,192,86,150,139,236,37,174,69,4,179,121,120,36,182,142,144,188,116,37,36,68,149,171,219,94,85,57,10,56,226,75,48,228,154,185,90,155,239,234,20,253,109,133,146,152,130,76,126,188,97,146,138,44,207,164,89,153,203,29,199,108,154,47,76,240,2,44,222,46,172,251,166,38,149,141,72,118,246,130,202,225,129,23,68,9,53,216,10,225,84,120,143,113,120,93,17,50,11,34,195,160,203,156,165,132,178,205,80,46,254,248,158,185,178,147,46,117,21,138,124,204,124,152,249,52,146,138,80,145,145,33,22,67,131,93,238,180,212,7,251,253,77,101,241,0,165,238,148,107,176,236,154,72,139,250,222,225,1,50,114,57,39,66,174,152,118,23,167,85,163,60,233,104,9,103,27,183,204,56,124,252,209,52,63,254,195,127,255,243,95,7,117,4,158,6,21,110,85,133,95,116,124,142,54,229,29,114,10,145,187,40,196,174,97,62,71,159,82,254,156,58,254,93,212,97,87,68,159,163,78,41,127,78,157,241,109,234,212,69,8,101,91,72,199,145,211,237,133,9,122,102,81,55,245,200,188,178,65,111,113,101,85,221,93,113,217,97,171,234,147,130,234,39,63,50,205,85,114,57,168,195,164,200,167,19,54,127,89,124,126,225,114,167,79,129,47,93,238,202,48,180,229,142,107,232,223,93,67,30,134,119,214,49,135,82,212,146,220,93,75,49,121,239,172,102,30,166,168,231,248,238,122,242,89,116,103,53,115,40,69,45,39,119,215,82,78,153,59,235,89,192,217,188,25,227,207,20,255,51,235,44,251,216,23,7,215,175,179,230,106,91,40,194,174,122,36,184,236,47,54,84,165,155,54,177,203,226,125,42,198,220,131,60,217,128,255,209,181,83,105,54,224,151,216,48,85,138,219,247,74,153,176,209,72,192,104,103,185,82,46,14,178,203,209,77,79,151,28,226,156,35,88,247,215,174,6,10,209,32,158,162,190,173,93,151,240,113,76,111,124,182,107,102,221,91,99,31,77,62,181,197,2,21,36,243,82,207,7,252,133,98,139,163,225,60,196,47,15,21,171,248,202,239,179,97,17,172,111,59,115,103,143,125,255,247,137,230,19,118,79,88,80,107,7,55,176,94,187,57,129,93,60,11,24,118,17,236,99,118,209,111,62,96,166,72,211,251,12,38,18,191,186,47,56,172,243,178,37,29,16,195,206,133,221,125,42,139,138,29,225,140,224,169,83,209,28,4,42,112,187,104,106,155,217,222,77,44,44,12,141,157,8,192,194,58,162,242,81,17,44,29,7,235,199,188,92,203,3,192,215,24,187,93,241,109,45,253,48,140,90,108,161,89,217,252,70,210,50,81,228,9,201,8,184,167,158,15,126,181,210,133,135,221,183,243,167,146,239,44,58,243,98,208,135,82,56,62,178,129,153,182,3,103,196,7,124,5,218,167,225,190,56,249,153,237,21,95,14,77,78,55,171,250,18,198,162,26,212,113,34,18,206,35,106,153,67,52,54,104,104,200,163,48,252,178,196,228,49,66,2,67,181,95,72,231,176,241,212,4,19,244,176,224,211,182,151,200,199,132,65,204,16,101,152,134,27,226,216,8,66,106,224,107,47,166,70,235,195,7,30,233,37,171,230,250,170,200,31,180,191,177,59,68,236,227,201,150,73,39,218,215,238,17,212,236,18,205,95,146,228,68,73,64,107,131,133,51,31,112,219,41,45,202,12,93,180,103,24,241,135,32,166,188,248,185,107,206,80,20,33,12,51,238,18,235,9,204,67,115,61,11,188,237,239,58,156,52,167,228,216,246,76,131,103,64,17,237,114,88,177,247,43,100,28,21,114,114,214,193,198,195,204,221,167,172,214,116,233,252,252,71,233,130,174,111,209,133,85,98,252,65,202,196,20,71,183,104,195,139,96,190,173,57,62,245,46,19,130,185,2,252,185,188,112,246,86,60,19,36,67,123,13,45,223,40,8,128,152,159,222,233,75,252,123,9,254,209,89,123,226,87,11,105,27,204,3,91,82,222,112,126,117,105,173,247,173,154,82,213,180,139,230,198,66,157,19,247,38,141,157,183,136,206,106,36,76,192,228,236,241,19,240,32,66,88,221,192,208,155,195,175,58,108,209,27,101,122,214,162,36,158,89,203,235,22,141,171,55,173,44,122,96,129,40,84,63,220,81,111,173,12,171,85,98,174,247,31,191,178,60,85,244,244,77,133,251,187,254,96,96,188,236,25,29,131,143,221,184,109,91,121,137,146,75,252,223,219,236,243,162,50,150,30,85,45,149,45,218,127,103,151,165,149,91,252,105,253,79,229,64,110,17,163,206,234,79,224,20,62,143,196,211,50,118,141,105,226,251,55,247,245,195,59,98,67,192,176,139,100,213,91,194,157,156,84,208,250,80,239,51,70,126,241,30,87,184,230,0,118,136,165,192,97,66,217,234,83,236,19,21,51,224,246,162,170,156,223,181,34,84,126,114,208,239,13,179,135,238,146,215,146,124,73,106,107,203,43,11,236,201,27,230,139,70,171,89,10,32,46,128,228,29,3,171,34,178,248,62,75,211,67,131,170,154,144,58,77,117,157,180,142,38,47,16,24,2,63,56,167,67,129,222,183,140,68,59,235,170,48,207,29,191,196,161,111,35,224,218,9,45,158,133,11,75,197,253,110,231,55,189,154,181,181,182,219,220,109,24,242,153,92,39,101,143,90,89,9,115,107,189,167,72,208,76,172,76,68,159,33,85,228,14,65,87,85,129,170,110,133,215,180,88,230,69,240,41,8,23,1,207,104,236,56,197,207,64,105,18,90,221,83,70,103,237,135,78,174,148,251,225,195,180,229,32,95,116,34,246,109,170,64,164,104,229,182,142,233,56,185,136,179,151,178,87,190,118,77,196,225,126,90,199,41,171,72,247,101,221,166,250,204,138,52,21,37,171,200,84,148,180,254,82,17,68,193,165,250,74,235,43,237,182,210,36,171,83,146,60,230,94,121,14,83,97,85,58,132,76,119,165,180,166,173,174,102,170,159,84,108,155,70,27,245,88,233,229,75,115,28,199,8,86,33,173,244,70,175,180,19,163,146,107,147,88,168,132,3,33,174,28,53,235,37,157,7,93,86,179,24,243,229,32,246,121,4,182,204,61,248,159,87,161,73,110,93,74,110,5,44,147,194,51,195,54,49,193,14,82,180,219,156,50,25,34,91,108,19,66,119,16,146,59,212,150,26,76,38,136,173,70,219,65,144,94,64,33,154,171,94,204,158,223,120,21,164,252,153,135,29,51,154,134,198,2,210,40,176,36,81,185,184,244,153,128,77,204,106,65,160,172,54,211,10,205,196,99,66,107,147,38,209,228,118,85,162,73,78,151,92,6,219,12,60,221,1,120,186,9,152,61,213,108,134,222,193,124,209,120,19,52,123,83,219,12,237,239,0,237,111,130,230,239,96,155,177,201,14,216,164,4,59,87,25,171,182,10,210,241,49,108,81,48,15,52,254,203,145,21,211,240,205,67,60,139,110,15,178,91,75,149,127,216,105,245,170,138,115,4,240,87,88,19,93,76,41,90,29,168,2,201,151,170,42,36,47,184,21,43,95,241,156,193,113,60,35,27,75,83,236,30,110,83,163,200,19,145,48,202,218,213,59,92,1,187,177,142,189,65,173,91,224,211,231,57,94,190,175,61,217,100,133,164,94,124,228,197,19,130,169,188,53,21,185,156,223,238,234,175,68,166,93,229,159,107,13,242,145,9,218,197,158,112,189,157,211,89,189,14,255,174,97,86,250,169,221,250,242,230,18,42,49,20,160,184,14,102,183,171,150,186,21,86,152,170,145,239,104,213,133,140,184,203,213,7,198,21,226,79,167,252,168,214,210,4,229,214,174,252,213,51,108,57,152,225,35,56,202,97,171,254,143,15,71,123,245,203,170,105,218,226,189,83,4,216,22,100,5,22,176,234,99,169,34,163,164,23,71,85,33,245,235,104,195,254,181,255,3,212,140,69,103,72,55,0,0 };
