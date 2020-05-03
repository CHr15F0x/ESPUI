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
"</button></div>");$("#btn"+data.id).on({touchstart:function(e){e.preventDefault();buttonclick(data.id,true);},touchend:function(e){e.preventDefault();buttonclick(data.id,false);}});$("#btn"+data.id).prop('disabled',!data.enabled);if(data.enabled){$("#btn"+data.id).css('background-color','#999999');}else{$("#btn"+data.id).css('background-color','#dddddd');}
break;case UI_SWITCHER:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
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
"</div>");if(!data.visible){$("#id"+data.id).hide();}
break;case UI_TEXT_INPUT:var parent;if(data.parentControl){parent=$("#tab"+data.parentControl);}else{parent=$("#row");}
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
"</div>");requestOrientationPermission();break;case UPDATE_LABEL:$("#l"+data.id).html(data.value);break;case UPDATE_SWITCHER:switcher(data.id,data.value=="0"?0:1);break;case UPDATE_SLIDER:slider_move($("#sl"+data.id),data.value,"100",false);break;case UPDATE_NUMBER:if(data.visible){$("#num"+data.id).val(data.value);$("#id"+data.id).show();}else{$("#id"+data.id).hide();}
break;case UPDATE_TEXT_INPUT:if(data.visible){$("#text"+data.id).val(data.value);$("#id"+data.id).show();}else{$("#id"+data.id).hide();}
break;case UPDATE_SELECT:$("#select"+data.id).val(data.value);break;case UPDATE_BUTTON:$("#btn"+data.id).prop('disabled',!data.enabled);if(data.enabled){$("#btn"+data.id).css('background-color','#999999');}else{$("#btn"+data.id).css('background-color','#dddddd');}
break;case UPDATE_PAD:case UPDATE_CPAD:break;case UPDATE_GAUGE:$("#gauge"+data.id).val(data.value);break;case UPDATE_ACCEL:break;default:console.error("Unknown type or event");break;}
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

const uint8_t JS_CONTROLS_GZIP[3423] PROGMEM = { 31,139,8,0,33,9,175,94,2,255,237,91,253,114,219,54,18,255,63,79,193,48,153,136,60,203,250,200,87,83,201,116,70,145,149,68,87,197,246,217,114,211,185,52,231,161,72,200,226,132,34,89,18,180,236,170,122,141,123,144,123,164,123,146,91,44,0,18,164,40,91,137,219,76,59,185,204,52,17,23,139,221,31,118,23,139,175,173,19,6,9,213,206,134,231,195,195,225,120,216,27,157,191,57,27,90,143,91,173,174,195,27,142,15,122,227,193,249,209,235,215,167,131,177,213,206,233,195,243,241,112,60,24,89,10,225,184,119,96,181,139,253,144,212,106,231,60,125,70,121,92,100,234,115,174,199,57,215,171,179,241,248,232,208,122,82,228,19,212,118,235,73,206,57,234,189,2,16,79,139,140,156,216,110,61,205,249,78,223,15,199,253,183,131,19,235,89,145,53,163,183,91,207,20,238,209,240,0,104,207,75,188,156,218,110,61,207,57,15,207,222,189,2,218,119,69,78,65,109,183,190,83,204,53,248,105,12,70,62,62,27,91,47,138,220,74,75,187,245,34,239,241,230,164,119,252,214,250,94,16,122,7,7,156,114,126,124,52,60,100,172,162,161,63,26,244,78,4,115,187,245,189,162,177,247,202,106,151,28,194,105,138,67,78,7,163,65,31,164,149,124,34,201,109,197,43,71,199,227,33,179,127,201,45,146,220,86,220,242,110,8,132,146,87,144,214,86,124,242,174,247,147,213,46,249,3,105,109,213,21,227,193,177,213,46,123,2,137,109,197,15,111,122,103,111,6,86,59,247,195,24,25,5,185,173,248,161,215,239,179,224,120,81,226,20,100,69,66,22,218,7,71,239,15,179,192,30,13,94,143,179,0,62,25,190,121,59,206,194,180,63,56,28,131,215,229,8,251,231,227,179,147,127,156,29,13,79,7,153,168,254,249,224,221,224,164,55,202,39,74,255,252,120,0,189,78,134,63,66,215,199,25,241,253,96,220,59,61,126,219,27,41,226,207,79,207,14,95,143,142,222,23,116,244,123,39,39,71,227,44,172,251,231,189,209,240,159,189,19,176,245,243,140,116,208,59,249,33,11,209,254,249,225,209,225,192,122,252,236,89,247,210,142,181,139,216,142,102,7,54,181,173,128,44,180,94,28,219,215,134,137,45,51,59,233,57,14,241,173,169,237,39,4,73,137,239,185,36,238,135,1,245,130,52,76,19,209,52,77,3,135,122,97,160,57,161,31,198,125,223,78,18,3,127,14,93,115,41,126,88,135,233,124,66,226,140,222,77,22,30,117,102,10,159,157,16,213,102,157,152,208,52,14,116,248,235,151,52,244,18,162,119,5,139,48,161,100,32,115,18,219,190,155,53,231,246,148,28,17,161,36,142,189,75,18,103,76,185,125,37,211,130,80,59,137,102,182,79,51,166,204,222,146,39,73,131,169,31,46,20,57,220,252,178,221,177,227,56,204,251,75,87,200,102,219,247,126,181,99,47,200,24,152,39,100,163,107,199,159,244,174,75,166,118,234,83,73,212,187,171,213,61,102,249,5,153,36,161,243,169,171,252,6,55,4,196,161,196,45,123,33,38,191,164,36,161,71,177,71,2,106,51,210,49,137,231,94,146,192,47,195,92,174,238,101,156,137,125,73,222,200,0,128,38,63,116,108,255,148,134,177,125,65,26,9,161,67,74,230,134,78,146,40,245,48,78,18,189,254,247,211,163,195,70,66,97,20,23,222,244,218,200,194,199,52,187,138,224,24,244,135,177,34,219,3,15,99,4,129,70,23,195,173,160,235,162,82,87,46,188,235,77,141,172,235,125,43,72,125,223,92,230,178,16,84,100,199,9,201,185,204,46,183,97,174,242,131,231,126,4,144,156,252,225,99,25,175,29,83,48,193,67,195,13,157,116,14,150,51,27,182,235,26,250,223,116,179,17,78,167,48,41,30,26,250,131,56,92,192,247,140,206,125,67,215,205,174,112,69,195,241,67,208,13,65,205,165,168,162,97,214,157,130,23,210,100,0,177,17,131,134,13,238,99,210,51,94,208,17,147,121,120,73,248,100,210,113,150,236,94,196,132,4,186,185,198,10,56,11,124,49,113,43,184,56,104,68,161,53,181,195,80,19,8,24,200,71,15,94,60,127,242,172,91,209,43,31,122,129,26,24,75,199,247,156,79,29,97,185,85,97,204,51,59,112,125,242,163,151,120,19,207,247,232,117,31,8,23,96,159,37,184,241,126,121,252,143,30,221,151,38,111,204,60,215,37,129,185,204,252,193,226,63,15,87,225,163,140,29,6,62,184,132,31,35,47,161,36,128,236,162,95,102,58,29,212,169,215,171,177,212,209,232,24,87,11,47,112,195,69,131,197,35,211,210,136,194,152,222,183,116,253,183,223,170,91,94,180,54,181,60,125,250,36,115,47,166,211,247,100,114,10,191,9,53,244,69,210,105,54,245,157,114,199,89,152,208,192,158,147,29,189,179,222,200,164,238,232,205,5,88,188,187,34,128,247,139,133,11,25,247,100,188,134,65,24,145,192,146,150,53,200,37,101,153,58,72,66,159,64,255,11,16,201,57,53,198,183,69,200,109,10,77,74,174,0,95,230,235,124,202,228,225,79,227,148,116,87,221,28,26,78,166,109,176,33,35,136,44,79,177,130,52,194,104,55,72,99,132,42,9,124,9,100,177,131,33,86,146,192,90,221,82,234,129,134,134,139,153,135,181,18,43,11,211,73,232,94,35,205,129,47,18,67,108,201,213,143,177,55,232,117,68,196,250,87,220,135,119,32,58,145,163,188,238,66,238,43,175,196,149,124,224,113,164,195,240,104,28,250,73,99,26,198,3,27,244,18,159,48,100,214,62,14,4,150,156,43,62,200,37,99,239,148,114,188,96,54,87,93,197,30,70,214,9,140,101,118,39,49,177,63,117,229,24,240,104,208,201,198,79,61,234,19,142,208,183,39,196,199,40,153,219,94,240,150,216,128,87,230,166,156,161,44,15,55,244,29,6,21,44,13,18,187,210,48,252,179,207,135,103,46,249,167,197,196,83,123,162,239,84,240,136,137,164,112,98,74,7,75,113,82,195,142,32,226,33,239,239,185,222,165,230,185,86,205,115,245,29,110,70,207,221,185,167,215,32,236,32,240,173,26,93,132,108,195,147,206,131,68,131,133,223,213,40,119,175,6,236,202,70,72,56,0,190,77,214,123,31,90,245,189,217,179,125,41,20,7,204,104,77,32,238,205,226,38,231,72,34,59,64,245,126,181,118,236,166,225,223,187,11,88,39,107,153,192,75,219,79,9,10,100,50,184,180,38,12,102,95,47,155,149,31,168,254,108,118,133,41,251,7,218,117,146,82,26,114,203,78,104,80,66,192,56,194,96,14,51,135,64,34,13,128,5,185,113,165,51,10,188,117,141,165,45,179,208,37,141,110,236,192,87,156,42,63,241,78,251,153,151,152,245,16,156,232,206,215,91,26,166,206,12,151,192,78,158,139,204,37,105,68,49,97,243,240,128,111,29,33,121,169,32,132,136,58,194,237,174,234,40,5,28,241,37,50,196,154,185,90,85,65,140,226,48,50,106,174,151,216,19,159,184,181,250,125,108,33,1,126,154,89,100,73,194,114,93,130,3,94,173,77,108,231,211,69,28,166,129,187,139,206,173,213,107,15,190,199,63,53,25,99,159,209,211,197,63,172,231,189,98,232,203,115,255,183,21,252,60,105,48,253,201,134,180,194,215,37,166,205,200,131,212,178,244,182,254,82,135,184,129,237,134,11,59,21,93,209,202,70,36,58,123,65,109,127,207,11,162,148,106,108,77,179,106,216,99,18,94,213,184,206,146,202,48,232,179,240,146,74,217,246,173,48,99,112,151,95,219,10,75,83,78,30,28,51,14,179,152,248,50,21,50,150,115,137,229,172,200,174,163,58,242,131,253,254,166,214,157,192,206,220,41,118,13,162,107,42,44,234,123,251,123,182,86,200,146,145,237,242,68,113,118,92,215,170,211,164,146,34,111,226,22,57,18,199,31,77,139,227,223,255,239,191,255,179,215,180,193,211,0,225,86,40,120,53,243,57,104,170,59,20,0,197,119,1,196,46,142,62,7,79,37,127,1,142,127,23,56,236,82,235,115,224,84,242,23,224,76,110,131,211,228,33,148,111,122,45,75,76,183,151,58,224,204,163,110,234,197,243,218,6,220,252,146,173,190,61,112,209,225,70,232,78,9,250,209,15,12,185,76,46,123,77,152,20,197,116,194,230,47,139,207,47,92,160,213,41,240,165,11,116,149,140,210,2,205,34,228,174,8,49,12,239,140,177,32,165,140,50,190,59,74,62,121,239,12,179,40,166,140,115,114,119,156,56,139,238,12,179,32,165,140,210,185,59,74,49,101,238,140,179,36,71,65,90,218,140,225,195,202,95,102,157,101,31,187,252,168,253,251,172,185,202,22,42,102,151,83,66,184,232,207,55,84,149,155,54,190,203,194,62,53,109,238,65,158,108,193,191,246,149,85,107,183,224,23,223,48,213,202,7,142,90,149,178,243,115,46,70,57,125,86,114,161,144,109,14,155,106,186,68,17,167,40,193,184,191,118,153,81,138,6,254,120,246,109,237,186,184,143,19,122,237,179,93,51,235,222,153,248,112,158,233,242,5,42,72,231,149,158,15,240,77,229,6,71,195,9,14,175,59,37,43,255,42,238,179,97,17,108,22,221,197,110,105,185,32,118,107,234,19,126,88,99,150,201,50,203,12,124,104,172,31,171,242,167,204,255,251,79,241,31,187,5,45,193,218,194,101,172,215,31,238,176,222,171,142,112,64,2,187,28,118,179,43,45,202,119,143,179,152,76,173,154,226,32,128,128,118,81,96,235,249,62,143,47,66,76,26,59,61,128,133,85,137,210,71,101,97,217,56,88,63,230,229,70,81,0,124,77,136,219,231,223,198,210,15,195,168,195,22,165,149,137,247,173,134,110,71,30,215,108,3,247,212,243,193,175,70,182,72,177,215,4,124,8,122,104,208,153,151,0,30,74,225,168,201,6,166,155,22,156,39,31,224,106,181,75,195,93,126,74,212,187,43,92,58,117,164,235,117,117,185,99,81,13,112,172,40,14,231,17,53,244,177,61,209,104,168,137,99,51,252,50,248,68,211,194,24,134,106,190,20,206,97,227,105,112,38,232,97,192,167,105,46,109,159,196,76,196,204,166,76,166,230,134,36,209,130,144,106,228,202,75,168,214,249,249,103,140,244,138,21,118,125,5,197,231,250,111,236,134,148,248,196,185,97,210,241,246,181,59,7,57,187,120,243,118,243,171,104,108,94,240,208,217,96,225,220,7,104,59,137,162,202,208,101,123,134,17,62,115,49,240,252,231,182,57,67,82,184,50,194,184,43,172,199,101,238,235,235,89,224,221,112,219,225,100,57,165,192,182,163,107,152,1,121,180,139,97,37,222,175,144,113,100,200,137,89,7,155,20,189,112,247,178,90,195,210,251,233,107,97,177,175,110,193,194,234,76,190,18,152,132,146,232,22,52,88,226,243,109,205,241,169,119,145,198,4,1,96,49,64,233,156,46,121,28,91,132,246,154,180,98,35,39,128,196,226,244,206,234,12,62,8,225,31,173,181,2,6,185,144,118,193,60,176,125,197,134,211,203,11,99,189,111,93,23,80,179,46,138,27,75,85,92,232,77,154,88,239,108,58,107,224,221,181,193,158,118,65,30,68,8,171,138,24,123,115,248,213,132,237,124,171,10,103,35,74,147,153,177,188,234,208,164,126,221,201,163,7,22,136,82,109,199,29,113,43,69,102,157,10,115,125,248,248,59,235,147,37,93,223,84,184,191,31,142,70,218,171,129,214,211,112,236,218,109,219,202,11,59,189,32,95,243,96,80,116,16,150,204,177,244,40,43,197,76,222,254,7,187,44,171,75,195,194,129,63,149,3,209,34,90,147,85,215,192,137,125,30,241,135,115,226,106,211,212,247,175,239,171,7,125,155,13,129,192,46,146,213,166,113,119,34,169,132,122,95,237,51,177,253,242,157,47,119,205,30,236,16,43,5,135,41,101,171,79,185,79,84,206,128,55,151,140,21,252,174,148,216,226,201,65,189,99,204,159,241,43,94,86,138,5,183,157,27,94,100,96,79,222,210,95,182,58,237,74,1,252,178,72,220,71,176,26,41,3,247,89,10,14,69,84,93,135,212,169,203,171,167,117,105,226,178,65,198,105,225,252,132,167,238,108,108,32,174,48,180,181,19,86,50,11,23,134,250,70,121,251,249,171,92,255,91,141,131,159,30,191,2,16,113,138,88,219,182,86,105,93,239,45,170,9,254,218,47,195,89,217,122,71,253,198,39,193,117,54,190,66,49,165,34,19,127,134,181,120,242,228,116,89,244,41,203,146,176,100,201,208,207,130,79,65,184,8,48,165,179,243,36,30,2,179,44,188,186,39,13,199,218,247,173,66,165,254,163,71,89,203,94,177,166,136,111,92,101,253,79,57,58,186,170,76,203,42,76,57,115,41,122,21,75,19,249,68,220,205,202,116,69,145,240,174,40,203,149,159,121,13,174,164,228,5,183,146,146,149,215,74,2,175,167,149,95,89,249,172,217,149,72,242,50,52,193,163,239,84,39,113,25,33,149,67,200,177,75,208,10,90,21,102,134,79,0,187,9,209,70,28,43,181,58,109,78,146,196,134,101,88,169,172,82,11,41,249,168,196,226,204,87,106,238,64,136,43,75,166,61,65,199,160,203,75,82,19,92,15,19,31,35,176,163,239,192,191,88,100,40,184,85,45,133,45,64,149,22,204,132,55,169,9,182,208,162,92,103,85,233,224,89,238,38,37,116,11,37,133,83,125,165,193,68,98,187,209,104,91,40,82,235,99,120,115,221,75,216,91,37,22,185,138,159,69,177,19,70,83,164,177,128,212,74,44,105,84,173,46,123,83,97,19,179,94,82,40,138,9,149,58,66,254,242,210,217,132,36,114,110,135,18,57,5,44,133,12,182,89,240,116,11,193,211,77,130,217,187,214,102,209,91,152,47,154,108,18,205,30,32,55,139,246,183,16,237,111,18,141,143,134,155,101,199,91,200,142,43,100,23,10,159,229,94,73,56,62,129,61,26,193,64,195,95,150,40,136,135,111,12,241,60,186,61,200,110,29,89,43,99,102,197,201,50,206,109,16,127,73,20,213,229,148,162,148,249,74,33,197,74,100,41,201,11,110,149,85,44,104,207,197,161,60,45,31,75,155,239,0,110,131,81,230,193,93,70,214,46,31,45,75,178,91,235,178,55,192,186,69,124,246,150,137,255,119,134,242,190,149,215,9,123,201,129,151,56,49,161,226,218,152,231,114,188,222,86,159,212,116,179,142,159,107,13,226,69,14,218,249,166,120,189,29,233,172,184,9,191,27,132,85,246,42,215,222,216,92,65,141,53,41,144,223,135,179,235,101,67,94,139,75,153,178,17,183,244,242,70,138,95,102,171,3,67,64,248,206,140,103,213,142,162,168,176,118,21,239,222,97,203,193,12,31,193,89,150,24,205,127,253,124,176,211,188,168,235,186,201,31,135,121,128,221,32,89,10,11,88,113,185,128,200,40,217,205,89,157,107,253,125,208,176,255,186,255,3,2,165,131,107,39,57,0,0 };
