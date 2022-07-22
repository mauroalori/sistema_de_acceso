String json_reload(String SOLICITUD_DE_VALIDACION,String pass_ingresada=""){
  String text_json=
  String("{\n")+
  "   \"validacion\":\"" + SOLICITUD_DE_VALIDACION + "\",\n"+
  "   \"pass_ingresada\":\"" + pass_ingresada + "\"\n"+
  "}";

  return text_json;
}
