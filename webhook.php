<?php
#$content = file_get_contents('php://input');
#$payload = json_decode($_REQUEST["payload"]);
$request_body = file_get_contents('php://input');
$data = json_decode($request_body);

#$data = '/\[data\].+/';
#preg_match($data,$payload[0],$result);
#print_r($result[0]);
#$req_dump = print_r(base64_decode($result[0]));
#$req_dump = print_r($payload);
$var = $data->data;
$out = print_r(base64_decode($var));
#--------------------------------------------------------------------

//Conversion coodernadas
#--------------------------------------------------------------------
//curl
$data_lugar=array( 'name'=>'Las vegas', 'latitude'=>"36.1141", 'longitude'=>"-115.1945", 'elevation'=>"0");
$data_json = json_encode($data_lugar);
$ch = curl_init();
$url='http://api-m2x.att.com/v2/devices/f1bc2105c405a76cfa8a46fcccec42bc/location';
curl_setopt($ch,CURLOPT_URL,$url);
curl_setopt($ch, CURLOPT_HTTPHEADER, array('X-M2X-KEY: 53701ca0a9bfb409b78a0f63a4374723','Content-Type: application/json','Content-Length: ' . strlen($data_json)));
curl_setopt($ch, CURLOPT_CUSTOMREQUEST, 'PUT');
curl_setopt($ch, CURLOPT_POSTFIELDS,$data_json);
curl_setopt($ch,CURLOPT_URL,$url);
curl_setopt($ch, CURLOPT_SSL_VERIFYPEER, false);
curl_setopt($ch, CURLOPT_RETURNTRANSFER, true);
$result=curl_exec($ch);
print_r($result);
curl_close($ch);

#------------------------------------------------------------------
//escribe archivo
$fp = fopen("request.log", "a");
fwrite($fp, $out,1024);
fclose($fp);
?>

