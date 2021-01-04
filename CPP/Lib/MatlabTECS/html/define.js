function CodeDefine() { 
this.def = new Array();
this.def["step"] = {file: "TECS_cpp.html",line:23,type:"fcn"};
this.def["initialize"] = {file: "TECS_cpp.html",line:371,type:"fcn"};
this.def["terminate"] = {file: "TECS_cpp.html",line:381,type:"fcn"};
this.def["getRTM"] = {file: "TECS_cpp.html",line:404,type:"fcn"};
this.def["B_TECS_T"] = {file: "TECS_h.html",line:45,type:"type"};
this.def["DW_TECS_T"] = {file: "TECS_h.html",line:51,type:"type"};
this.def["ExtU_TECS_T"] = {file: "TECS_h.html",line:61,type:"type"};
this.def["ExtY_TECS_T"] = {file: "TECS_h.html",line:67,type:"type"};
this.def["DiscretePIDController_I"] = {file: "TECS_h.html",line:71,type:"var"};
this.def["TECS_P"] = {file: "TECS_data_cpp.html",line:23,type:"var"};
this.def["int8_T"] = {file: "rtwtypes_h.html",line:51,type:"type"};
this.def["uint8_T"] = {file: "rtwtypes_h.html",line:52,type:"type"};
this.def["int16_T"] = {file: "rtwtypes_h.html",line:53,type:"type"};
this.def["uint16_T"] = {file: "rtwtypes_h.html",line:54,type:"type"};
this.def["int32_T"] = {file: "rtwtypes_h.html",line:55,type:"type"};
this.def["uint32_T"] = {file: "rtwtypes_h.html",line:56,type:"type"};
this.def["real32_T"] = {file: "rtwtypes_h.html",line:57,type:"type"};
this.def["real64_T"] = {file: "rtwtypes_h.html",line:58,type:"type"};
this.def["real_T"] = {file: "rtwtypes_h.html",line:64,type:"type"};
this.def["time_T"] = {file: "rtwtypes_h.html",line:65,type:"type"};
this.def["boolean_T"] = {file: "rtwtypes_h.html",line:66,type:"type"};
this.def["int_T"] = {file: "rtwtypes_h.html",line:67,type:"type"};
this.def["uint_T"] = {file: "rtwtypes_h.html",line:68,type:"type"};
this.def["ulong_T"] = {file: "rtwtypes_h.html",line:69,type:"type"};
this.def["char_T"] = {file: "rtwtypes_h.html",line:70,type:"type"};
this.def["uchar_T"] = {file: "rtwtypes_h.html",line:71,type:"type"};
this.def["byte_T"] = {file: "rtwtypes_h.html",line:72,type:"type"};
this.def["pointer_T"] = {file: "rtwtypes_h.html",line:90,type:"type"};
}
CodeDefine.instance = new CodeDefine();
var testHarnessInfo = {OwnerFileName: "", HarnessOwner: "", HarnessName: "", IsTestHarness: "0"};
var relPathToBuildDir = "../ert_main.c";
var fileSep = "\\";
var isPC = true;
function Html2SrcLink() {
	this.html2SrcPath = new Array;
	this.html2Root = new Array;
	this.html2SrcPath["TECS_cpp.html"] = "../TECS.cpp";
	this.html2Root["TECS_cpp.html"] = "TECS_cpp.html";
	this.html2SrcPath["TECS_h.html"] = "../TECS.h";
	this.html2Root["TECS_h.html"] = "TECS_h.html";
	this.html2SrcPath["TECS_private_h.html"] = "../TECS_private.h";
	this.html2Root["TECS_private_h.html"] = "TECS_private_h.html";
	this.html2SrcPath["TECS_types_h.html"] = "../TECS_types.h";
	this.html2Root["TECS_types_h.html"] = "TECS_types_h.html";
	this.html2SrcPath["TECS_data_cpp.html"] = "../TECS_data.cpp";
	this.html2Root["TECS_data_cpp.html"] = "TECS_data_cpp.html";
	this.html2SrcPath["rtwtypes_h.html"] = "../rtwtypes.h";
	this.html2Root["rtwtypes_h.html"] = "rtwtypes_h.html";
	this.html2SrcPath["rtmodel_h.html"] = "../rtmodel.h";
	this.html2Root["rtmodel_h.html"] = "rtmodel_h.html";
	this.getLink2Src = function (htmlFileName) {
		 if (this.html2SrcPath[htmlFileName])
			 return this.html2SrcPath[htmlFileName];
		 else
			 return null;
	}
	this.getLinkFromRoot = function (htmlFileName) {
		 if (this.html2Root[htmlFileName])
			 return this.html2Root[htmlFileName];
		 else
			 return null;
	}
}
Html2SrcLink.instance = new Html2SrcLink();
var fileList = [
"TECS_cpp.html","TECS_h.html","TECS_private_h.html","TECS_types_h.html","TECS_data_cpp.html","rtwtypes_h.html","rtmodel_h.html"];
