xof 0302txt 0064
template Header {
 <3D82AB43-62DA-11cf-AB39-0020AF71E433>
 WORD major;
 WORD minor;
 DWORD flags;
}

template Vector {
 <3D82AB5E-62DA-11cf-AB39-0020AF71E433>
 FLOAT x;
 FLOAT y;
 FLOAT z;
}

template Coords2d {
 <F6F23F44-7686-11cf-8F52-0040333594A3>
 FLOAT u;
 FLOAT v;
}

template Matrix4x4 {
 <F6F23F45-7686-11cf-8F52-0040333594A3>
 array FLOAT matrix[16];
}

template ColorRGBA {
 <35FF44E0-6C7C-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
 FLOAT alpha;
}

template ColorRGB {
 <D3E16E81-7835-11cf-8F52-0040333594A3>
 FLOAT red;
 FLOAT green;
 FLOAT blue;
}

template IndexedColor {
 <1630B820-7842-11cf-8F52-0040333594A3>
 DWORD index;
 ColorRGBA indexColor;
}

template Boolean {
 <4885AE61-78E8-11cf-8F52-0040333594A3>
 WORD truefalse;
}

template Boolean2d {
 <4885AE63-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template MaterialWrap {
 <4885AE60-78E8-11cf-8F52-0040333594A3>
 Boolean u;
 Boolean v;
}

template TextureFilename {
 <A42790E1-7810-11cf-8F52-0040333594A3>
 STRING filename;
}

template Material {
 <3D82AB4D-62DA-11cf-AB39-0020AF71E433>
 ColorRGBA faceColor;
 FLOAT power;
 ColorRGB specularColor;
 ColorRGB emissiveColor;
 [...]
}

template MeshFace {
 <3D82AB5F-62DA-11cf-AB39-0020AF71E433>
 DWORD nFaceVertexIndices;
 array DWORD faceVertexIndices[nFaceVertexIndices];
}

template MeshFaceWraps {
 <4885AE62-78E8-11cf-8F52-0040333594A3>
 DWORD nFaceWrapValues;
 Boolean2d faceWrapValues;
}

template MeshTextureCoords {
 <F6F23F40-7686-11cf-8F52-0040333594A3>
 DWORD nTextureCoords;
 array Coords2d textureCoords[nTextureCoords];
}

template MeshMaterialList {
 <F6F23F42-7686-11cf-8F52-0040333594A3>
 DWORD nMaterials;
 DWORD nFaceIndexes;
 array DWORD faceIndexes[nFaceIndexes];
 [Material]
}

template MeshNormals {
 <F6F23F43-7686-11cf-8F52-0040333594A3>
 DWORD nNormals;
 array Vector normals[nNormals];
 DWORD nFaceNormals;
 array MeshFace faceNormals[nFaceNormals];
}

template MeshVertexColors {
 <1630B821-7842-11cf-8F52-0040333594A3>
 DWORD nVertexColors;
 array IndexedColor vertexColors[nVertexColors];
}

template Mesh {
 <3D82AB44-62DA-11cf-AB39-0020AF71E433>
 DWORD nVertices;
 array Vector vertices[nVertices];
 DWORD nFaces;
 array MeshFace faces[nFaces];
 [...]
}

Header{
1;
0;
1;
}

Mesh {
 177;
 0.01201;73.80683;-0.09690;,
 9.45141;69.76643;-18.08220;,
 0.01201;69.76643;-20.40880;,
 0.01201;73.80683;-0.09690;,
 16.72831;69.76643;-11.63540;,
 0.01201;73.80683;-0.09690;,
 20.17581;69.76643;-2.54530;,
 0.01201;73.80683;-0.09690;,
 19.00390;69.76643;7.10570;,
 0.01201;73.80683;-0.09690;,
 13.48131;69.76643;15.10670;,
 0.01201;73.80683;-0.09690;,
 4.87291;69.76643;19.62470;,
 0.01201;73.80683;-0.09690;,
 -4.84889;69.76643;19.62470;,
 0.01201;73.80683;-0.09690;,
 -13.45729;69.76643;15.10670;,
 0.01201;73.80683;-0.09690;,
 -18.97989;69.76643;7.10570;,
 0.01201;73.80683;-0.09690;,
 -20.15179;69.76643;-2.54530;,
 0.01201;73.80683;-0.09690;,
 -16.70429;69.76643;-11.63540;,
 0.01201;73.80683;-0.09690;,
 -9.42739;69.76643;-18.08220;,
 0.01201;73.80683;-0.09690;,
 0.01201;69.76643;-20.40880;,
 17.45370;58.26058;-33.32940;,
 0.01201;58.26058;-37.62840;,
 30.89971;58.26058;-21.41720;,
 37.26981;58.26058;-4.62080;,
 35.10450;58.26058;13.21190;,
 24.89990;58.26058;27.99570;,
 8.99391;58.26058;36.34390;,
 -8.96989;58.26058;36.34390;,
 -24.87589;58.26058;27.99570;,
 -35.08049;58.26058;13.21190;,
 -37.24579;58.26058;-4.62090;,
 -30.87569;58.26058;-21.41720;,
 -17.42970;58.26058;-33.32940;,
 0.01201;58.26058;-37.62840;,
 18.68250;35.88859;-35.28139;,
 0.01201;35.88859;-40.89830;,
 33.74141;35.88859;-23.84300;,
 40.91780;41.04098;-6.00770;,
 38.08871;41.04098;14.03210;,
 26.38481;41.04098;29.70900;,
 11.74741;41.04098;43.55600;,
 -11.72339;41.04098;43.55600;,
 -26.76550;41.04098;30.71360;,
 -38.06199;41.04098;14.19090;,
 -40.89109;41.04098;-6.00770;,
 -32.56820;35.88859;-24.54260;,
 -17.75089;35.88859;-35.28139;,
 0.01201;35.88859;-40.89830;,
 10.04311;28.17228;-38.85889;,
 0.01201;28.17228;-40.81750;,
 37.06651;28.17228;-26.13820;,
 44.92861;20.72918;-6.49470;,
 41.86641;20.72918;15.46480;,
 29.06400;20.72918;32.73320;,
 12.71431;20.72918;47.47890;,
 -12.69029;20.72918;47.47890;,
 -29.44469;20.72918;33.73780;,
 -41.83969;20.72918;15.62360;,
 -44.90189;20.72918;-6.49470;,
 -35.89329;28.17228;-26.83770;,
 -8.38809;28.17228;-38.85889;,
 0.01201;28.17228;-40.81750;,
 10.94788;0.41738;-43.51720;,
 0.01201;0.41738;-44.97789;,
 40.36881;0.41738;-27.95320;,
 48.69161;0.41738;-6.00770;,
 45.86251;0.41738;17.29190;,
 32.52961;0.41738;36.60790;,
 11.74741;0.41738;47.51530;,
 -11.72339;0.41738;47.51530;,
 -32.50560;0.41738;36.60790;,
 -45.83849;0.41738;17.29190;,
 -48.66759;0.41738;-6.00770;,
 -40.34479;0.41738;-27.95320;,
 -8.19716;0.41738;-43.51720;,
 0.01201;0.41738;-44.97789;,
 17.45370;-0.18511;-33.32940;,
 0.01201;-0.18511;-37.62840;,
 30.89971;-0.18511;-21.41720;,
 37.26981;-0.18511;-4.62080;,
 35.10450;-0.18511;13.21190;,
 24.89990;-0.18511;27.99570;,
 8.99391;-0.18511;36.34390;,
 -8.96989;-0.18511;36.34390;,
 -24.87589;-0.18511;27.99570;,
 -35.08049;-0.18511;13.21190;,
 -37.24579;-0.18511;-4.62090;,
 -30.87569;-0.18511;-21.41720;,
 -17.42970;-0.18511;-33.32940;,
 0.01201;-0.18511;-37.62840;,
 9.45141;0.05518;-18.08220;,
 0.01201;0.05518;-20.40880;,
 16.72831;0.05518;-11.63540;,
 20.17581;0.05518;-2.54530;,
 19.00390;0.05518;7.10570;,
 13.48131;0.05518;15.10670;,
 4.87291;0.05518;19.62470;,
 -4.84889;0.05518;19.62470;,
 -13.45729;0.05518;15.10670;,
 -18.97989;0.05518;7.10570;,
 -20.15179;0.05518;-2.54530;,
 -16.70429;0.05518;-11.63540;,
 -9.42739;0.05518;-18.08220;,
 0.01201;0.05518;-20.40880;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 0.01201;0.01888;-0.09690;,
 1.88147;17.81257;93.13097;,
 1.76927;27.08068;85.73403;,
 9.42723;30.25239;85.67858;,
 9.64793;21.11936;92.98248;,
 12.59926;37.90908;85.54501;,
 12.79918;28.94689;92.70586;,
 9.42723;45.56599;85.41131;,
 9.48925;36.70966;92.46325;,
 1.76926;48.73743;85.35598;,
 1.65706;39.86036;92.39679;,
 -5.88871;45.56599;85.41131;,
 -6.10941;36.55364;92.54528;,
 -9.06074;37.90908;85.54501;,
 -9.26065;28.72622;92.82187;,
 -5.88871;30.25239;85.67858;,
 -5.95073;20.96334;93.06453;,
 1.76927;27.08068;85.73403;,
 1.88147;17.81257;93.13097;,
 1.76927;35.11449;73.20425;,
 9.37790;38.26557;73.14931;,
 12.52951;45.87310;73.01659;,
 9.37790;53.48058;72.88357;,
 1.76926;56.63168;72.82864;,
 -5.83939;53.48058;72.88357;,
 -8.99098;45.87310;73.01659;,
 -5.83938;38.26557;73.14931;,
 1.76927;35.11449;73.20425;,
 1.76927;45.90589;56.01720;,
 8.65641;48.75825;55.96748;,
 11.50915;55.64429;55.84731;,
 8.65641;62.53029;55.72709;,
 1.76927;65.38276;55.67727;,
 -5.11788;62.53029;55.72709;,
 -7.97062;55.64429;55.84731;,
 -5.11788;48.75825;55.96748;,
 1.76927;45.90589;56.01720;,
 1.76927;55.30430;36.37050;,
 1.76927;55.30430;36.37050;,
 1.76927;55.30430;36.37050;,
 1.76927;55.30430;36.37050;,
 1.76927;55.30430;36.37050;,
 1.76927;55.30430;36.37050;,
 1.76927;55.30430;36.37050;,
 1.76927;55.30430;36.37050;,
 1.76927;28.83656;92.76386;,
 1.88147;17.81257;93.13097;,
 9.64793;21.11936;92.98248;,
 12.79918;28.94689;92.70586;,
 9.48925;36.70966;92.46325;,
 1.65706;39.86036;92.39679;,
 -6.10941;36.55364;92.54528;,
 -9.26065;28.72622;92.82187;,
 -5.95073;20.96334;93.06453;;
 
 144;
 3;0,1,2;,
 3;3,4,1;,
 3;5,6,4;,
 3;7,8,6;,
 3;9,10,8;,
 3;11,12,10;,
 3;13,14,12;,
 3;15,16,14;,
 3;17,18,16;,
 3;19,20,18;,
 3;21,22,20;,
 3;23,24,22;,
 3;25,26,24;,
 4;2,1,27,28;,
 4;1,4,29,27;,
 4;4,6,30,29;,
 4;6,8,31,30;,
 4;8,10,32,31;,
 4;10,12,33,32;,
 4;12,14,34,33;,
 4;14,16,35,34;,
 4;16,18,36,35;,
 4;18,20,37,36;,
 4;20,22,38,37;,
 4;22,24,39,38;,
 4;24,26,40,39;,
 4;28,27,41,42;,
 4;27,29,43,41;,
 4;29,30,44,43;,
 4;30,31,45,44;,
 4;31,32,46,45;,
 4;32,33,47,46;,
 4;33,34,48,47;,
 4;34,35,49,48;,
 4;35,36,50,49;,
 4;36,37,51,50;,
 4;37,38,52,51;,
 4;38,39,53,52;,
 4;39,40,54,53;,
 4;42,41,55,56;,
 4;41,43,57,55;,
 4;43,44,58,57;,
 4;44,45,59,58;,
 4;45,46,60,59;,
 4;46,47,61,60;,
 4;47,48,62,61;,
 4;48,49,63,62;,
 4;49,50,64,63;,
 4;50,51,65,64;,
 4;51,52,66,65;,
 4;52,53,67,66;,
 4;53,54,68,67;,
 4;56,55,69,70;,
 4;55,57,71,69;,
 4;57,58,72,71;,
 4;58,59,73,72;,
 4;59,60,74,73;,
 4;60,61,75,74;,
 4;61,62,76,75;,
 4;62,63,77,76;,
 4;63,64,78,77;,
 4;64,65,79,78;,
 4;65,66,80,79;,
 4;66,67,81,80;,
 4;67,68,82,81;,
 4;70,69,83,84;,
 4;69,71,85,83;,
 4;71,72,86,85;,
 4;72,73,87,86;,
 4;73,74,88,87;,
 4;74,75,89,88;,
 4;75,76,90,89;,
 4;76,77,91,90;,
 4;77,78,92,91;,
 4;78,79,93,92;,
 4;79,80,94,93;,
 4;80,81,95,94;,
 4;81,82,96,95;,
 4;84,83,97,98;,
 4;83,85,99,97;,
 4;85,86,100,99;,
 4;86,87,101,100;,
 4;87,88,102,101;,
 4;88,89,103,102;,
 4;89,90,104,103;,
 4;90,91,105,104;,
 4;91,92,106,105;,
 4;92,93,107,106;,
 4;93,94,108,107;,
 4;94,95,109,108;,
 4;95,96,110,109;,
 3;98,97,111;,
 3;97,99,112;,
 3;99,100,113;,
 3;100,101,114;,
 3;101,102,115;,
 3;102,103,116;,
 3;103,104,117;,
 3;104,105,118;,
 3;105,106,119;,
 3;106,107,120;,
 3;107,108,121;,
 3;108,109,122;,
 3;109,110,123;,
 4;124,125,126,127;,
 4;127,126,128,129;,
 4;129,128,130,131;,
 4;131,130,132,133;,
 4;133,132,134,135;,
 4;135,134,136,137;,
 4;137,136,138,139;,
 4;139,138,140,141;,
 4;125,142,143,126;,
 4;126,143,144,128;,
 4;128,144,145,130;,
 4;130,145,146,132;,
 4;132,146,147,134;,
 4;134,147,148,136;,
 4;136,148,149,138;,
 4;138,149,150,140;,
 4;142,151,152,143;,
 4;143,152,153,144;,
 4;144,153,154,145;,
 4;145,154,155,146;,
 4;146,155,156,147;,
 4;147,156,157,148;,
 4;148,157,158,149;,
 4;149,158,159,150;,
 3;151,160,152;,
 3;152,161,153;,
 3;153,162,154;,
 3;154,163,155;,
 3;155,164,156;,
 3;156,165,157;,
 3;157,166,158;,
 3;158,167,159;,
 3;168,169,170;,
 3;168,170,171;,
 3;168,171,172;,
 3;168,172,173;,
 3;168,173,174;,
 3;168,174,175;,
 3;168,175,176;,
 3;168,176,169;;
 
 MeshMaterialList {
  3;
  144;
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  2,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  2,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  1,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0,
  0;;
  Material {
   0.800000;0.000000;0.024800;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.442400;0.442400;0.442400;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
  Material {
   0.000000;0.000000;0.000000;1.000000;;
   5.000000;
   0.000000;0.000000;0.000000;;
   0.000000;0.000000;0.000000;;
  }
 }
 MeshNormals {
  150;
  -0.000000;1.000000;0.000000;,
  0.000000;0.924187;-0.381940;,
  0.177497;0.924187;-0.338191;,
  0.314331;0.924187;-0.216968;,
  0.379155;0.924187;-0.046038;,
  0.357121;0.924187;0.135438;,
  0.253274;0.924187;0.285886;,
  0.091404;0.924187;0.370842;,
  -0.091404;0.924187;0.370842;,
  -0.253274;0.924187;0.285886;,
  -0.357121;0.924187;0.135438;,
  -0.379155;0.924187;-0.046038;,
  -0.314331;0.924187;-0.216968;,
  -0.177497;0.924187;-0.338191;,
  -0.001927;0.528800;-0.848744;,
  0.391279;0.529190;-0.752900;,
  0.678072;0.546764;-0.491190;,
  0.822273;0.559210;-0.105598;,
  0.778790;0.548790;0.303835;,
  0.571704;0.561169;0.598534;,
  0.222168;0.620480;0.752094;,
  -0.214480;0.625961;0.749781;,
  -0.564597;0.575113;0.592009;,
  -0.777490;0.554371;0.296956;,
  -0.823467;0.556591;-0.110037;,
  -0.677354;0.540230;-0.499343;,
  -0.391620;0.524333;-0.756114;,
  -0.008163;0.082713;-0.996540;,
  0.416043;0.129021;-0.900145;,
  0.769621;0.219610;-0.599546;,
  0.967961;0.226876;-0.107607;,
  0.911730;0.182920;0.367817;,
  0.711052;0.196617;0.675090;,
  0.324990;0.270479;0.906213;,
  -0.306925;0.277777;0.910295;,
  -0.706652;0.213456;0.674596;,
  -0.916221;0.189725;0.352906;,
  -0.966953;0.224361;-0.121096;,
  -0.757414;0.211246;-0.617818;,
  -0.415781;0.117066;-0.901899;,
  -0.016289;0.102411;-0.994609;,
  0.340702;0.140125;-0.929671;,
  0.742785;0.214944;-0.634090;,
  0.971202;0.217461;-0.097353;,
  0.908177;0.205100;0.364894;,
  0.710785;0.180226;0.679929;,
  0.327811;0.130498;0.935687;,
  -0.312267;0.121448;0.942200;,
  -0.710492;0.167507;0.683478;,
  -0.914708;0.198644;0.351924;,
  -0.968742;0.222278;-0.110138;,
  -0.724637;0.215756;-0.654486;,
  -0.343140;0.129207;-0.930355;,
  -0.019720;0.157957;-0.987249;,
  0.304709;0.149667;-0.940613;,
  0.737642;0.153621;-0.657483;,
  0.978593;0.175069;-0.108200;,
  0.908962;0.214726;0.357325;,
  0.690250;0.172690;0.702662;,
  0.297104;0.061619;0.952855;,
  -0.288080;0.043949;0.956597;,
  -0.692787;0.145082;0.706398;,
  -0.914577;0.202729;0.349929;,
  -0.976419;0.182739;-0.114947;,
  -0.721480;0.156328;-0.674558;,
  -0.308826;0.141128;-0.940590;,
  -0.000636;-0.999496;-0.031723;,
  0.010633;-0.999524;-0.028967;,
  0.017204;-0.999708;-0.016976;,
  0.019039;-0.999816;-0.002312;,
  0.017933;-0.999816;0.006801;,
  0.012718;-0.999816;0.014356;,
  0.004590;-0.999816;0.018622;,
  -0.004590;-0.999816;0.018622;,
  -0.012718;-0.999816;0.014356;,
  -0.017933;-0.999816;0.006801;,
  -0.019039;-0.999816;-0.002312;,
  -0.017667;-0.999664;-0.018960;,
  -0.011731;-0.999429;-0.031692;,
  -0.000000;-0.999982;0.006083;,
  -0.002827;-0.999982;0.005386;,
  -0.005006;-0.999982;0.003456;,
  -0.006039;-0.999982;0.000733;,
  -0.005688;-0.999982;-0.002157;,
  -0.004034;-0.999982;-0.004553;,
  -0.001456;-0.999982;-0.005907;,
  0.001456;-0.999982;-0.005907;,
  0.004034;-0.999982;-0.004553;,
  0.005688;-0.999982;-0.002157;,
  0.006039;-0.999982;0.000733;,
  0.005006;-0.999982;0.003456;,
  0.002827;-0.999982;0.005386;,
  0.000000;-1.000000;0.000000;,
  0.001079;-0.622435;-0.782671;,
  0.566812;-0.506622;-0.649660;,
  0.818973;-0.346565;-0.457357;,
  0.305708;0.291858;0.906290;,
  0.001631;0.340860;0.940112;,
  -0.305266;0.292152;0.906344;,
  -0.835918;0.352517;0.420681;,
  -0.562711;-0.511054;-0.649754;,
  0.000554;-0.740691;-0.671846;,
  0.619206;-0.575100;-0.534644;,
  0.976116;-0.129312;-0.174573;,
  0.622573;0.580504;0.524802;,
  -0.000992;0.743418;0.668826;,
  -0.626475;0.579792;0.520932;,
  -0.979370;0.131686;0.153275;,
  -0.617074;-0.577300;-0.534737;,
  0.000000;-0.844370;-0.535761;,
  0.657369;-0.632125;-0.410223;,
  0.999508;0.002186;-0.031287;,
  0.671477;0.648021;0.359427;,
  0.000000;0.869216;0.494433;,
  -0.671477;0.648020;0.359427;,
  -0.999508;0.002186;-0.031288;,
  -0.657369;-0.632125;-0.410223;,
  0.000000;-0.875828;-0.482623;,
  0.644026;-0.636159;-0.424890;,
  0.965241;-0.002091;-0.261353;,
  0.712479;0.697242;-0.078908;,
  -0.000000;0.999991;-0.004249;,
  -0.712479;0.697243;-0.078909;,
  -0.965241;-0.002091;-0.261354;,
  -0.644026;-0.636160;-0.424890;,
  0.632459;-0.640161;-0.436106;,
  0.004923;0.033333;0.999432;,
  -0.001270;-0.997004;-0.077338;,
  0.027731;-0.997145;-0.070236;,
  0.045875;-0.998070;-0.041861;,
  0.051912;-0.998632;-0.006303;,
  0.048895;-0.998632;0.018543;,
  0.034677;-0.998632;0.039142;,
  0.012515;-0.998632;0.050773;,
  -0.012515;-0.998632;0.050773;,
  -0.034677;-0.998632;0.039142;,
  -0.048895;-0.998632;0.018543;,
  -0.051912;-0.998632;-0.006303;,
  -0.046801;-0.997853;-0.045826;,
  -0.029921;-0.996684;-0.075670;,
  0.826817;0.358081;0.433765;,
  -0.814494;-0.353540;-0.460010;,
  0.632462;0.624549;-0.458182;,
  -0.632462;0.624549;-0.458182;,
  -0.632459;-0.640162;-0.436106;,
  0.004924;0.033332;0.999432;,
  0.004920;0.033335;0.999432;,
  0.004923;0.033336;0.999432;,
  0.004923;0.033337;0.999432;,
  0.004927;0.033336;0.999432;;
  144;
  3;0,2,1;,
  3;0,3,2;,
  3;0,4,3;,
  3;0,5,4;,
  3;0,6,5;,
  3;0,7,6;,
  3;0,8,7;,
  3;0,9,8;,
  3;0,10,9;,
  3;0,11,10;,
  3;0,12,11;,
  3;0,13,12;,
  3;0,1,13;,
  4;1,2,15,14;,
  4;2,3,16,15;,
  4;3,4,17,16;,
  4;4,5,18,17;,
  4;5,6,19,18;,
  4;6,7,20,19;,
  4;7,8,21,20;,
  4;8,9,22,21;,
  4;9,10,23,22;,
  4;10,11,24,23;,
  4;11,12,25,24;,
  4;12,13,26,25;,
  4;13,1,14,26;,
  4;14,15,28,27;,
  4;15,16,29,28;,
  4;16,17,30,29;,
  4;17,18,31,30;,
  4;18,19,32,31;,
  4;19,20,33,32;,
  4;20,21,34,33;,
  4;21,22,35,34;,
  4;22,23,36,35;,
  4;23,24,37,36;,
  4;24,25,38,37;,
  4;25,26,39,38;,
  4;26,14,27,39;,
  4;27,28,41,40;,
  4;28,29,42,41;,
  4;29,30,43,42;,
  4;30,31,44,43;,
  4;31,32,45,44;,
  4;32,33,46,45;,
  4;33,34,47,46;,
  4;34,35,48,47;,
  4;35,36,49,48;,
  4;36,37,50,49;,
  4;37,38,51,50;,
  4;38,39,52,51;,
  4;39,27,40,52;,
  4;40,41,54,53;,
  4;41,42,55,54;,
  4;42,43,56,55;,
  4;43,44,57,56;,
  4;44,45,58,57;,
  4;45,46,59,58;,
  4;46,47,60,59;,
  4;47,48,61,60;,
  4;48,49,62,61;,
  4;49,50,63,62;,
  4;50,51,64,63;,
  4;51,52,65,64;,
  4;52,40,53,65;,
  4;127,128,67,66;,
  4;128,129,68,67;,
  4;129,130,69,68;,
  4;130,131,70,69;,
  4;131,132,71,70;,
  4;132,133,72,71;,
  4;133,134,73,72;,
  4;134,135,74,73;,
  4;135,136,75,74;,
  4;136,137,76,75;,
  4;137,138,77,76;,
  4;138,139,78,77;,
  4;139,127,66,78;,
  4;66,67,80,79;,
  4;67,68,81,80;,
  4;68,69,82,81;,
  4;69,70,83,82;,
  4;70,71,84,83;,
  4;71,72,85,84;,
  4;72,73,86,85;,
  4;73,74,87,86;,
  4;74,75,88,87;,
  4;75,76,89,88;,
  4;76,77,90,89;,
  4;77,78,91,90;,
  4;78,66,79,91;,
  3;79,80,92;,
  3;80,81,92;,
  3;81,82,92;,
  3;82,83,92;,
  3;83,84,92;,
  3;84,85,92;,
  3;85,86,92;,
  3;86,87,92;,
  3;87,88,92;,
  3;88,89,92;,
  3;89,90,92;,
  3;90,91,92;,
  3;91,79,92;,
  4;93,101,102,94;,
  4;94,102,103,95;,
  4;140,140,104,96;,
  4;96,104,105,97;,
  4;97,105,106,98;,
  4;98,106,107,99;,
  4;141,141,108,100;,
  4;100,108,101,93;,
  4;101,109,110,102;,
  4;102,110,111,103;,
  4;103,111,112,104;,
  4;104,112,113,105;,
  4;105,113,114,106;,
  4;106,114,115,107;,
  4;107,115,116,108;,
  4;108,116,109,101;,
  4;109,117,118,110;,
  4;110,118,119,111;,
  4;111,119,120,112;,
  4;112,120,121,113;,
  4;113,121,122,114;,
  4;114,122,123,115;,
  4;115,123,124,116;,
  4;116,124,117,109;,
  3;117,125,118;,
  3;118,125,119;,
  3;119,142,120;,
  3;120,142,121;,
  3;121,143,122;,
  3;122,143,123;,
  3;123,144,124;,
  3;124,144,117;,
  3;126,145,146;,
  3;126,146,147;,
  3;126,147,96;,
  3;126,96,97;,
  3;126,97,98;,
  3;126,98,148;,
  3;126,148,149;,
  3;126,149,145;;
 }
 MeshTextureCoords {
  177;
  0.038460;0.000000;,
  0.076920;0.125000;,
  0.000000;0.125000;,
  0.115380;0.000000;,
  0.153850;0.125000;,
  0.192310;0.000000;,
  0.230770;0.125000;,
  0.269230;0.000000;,
  0.307690;0.125000;,
  0.346150;0.000000;,
  0.384620;0.125000;,
  0.423080;0.000000;,
  0.461540;0.125000;,
  0.500000;0.000000;,
  0.538460;0.125000;,
  0.576920;0.000000;,
  0.615380;0.125000;,
  0.653850;0.000000;,
  0.692310;0.125000;,
  0.730770;0.000000;,
  0.769230;0.125000;,
  0.807690;0.000000;,
  0.846150;0.125000;,
  0.884620;0.000000;,
  0.923080;0.125000;,
  0.961540;0.000000;,
  1.000000;0.125000;,
  0.076920;0.250000;,
  0.000000;0.250000;,
  0.153850;0.250000;,
  0.230770;0.250000;,
  0.307690;0.250000;,
  0.384620;0.250000;,
  0.461540;0.250000;,
  0.538460;0.250000;,
  0.615380;0.250000;,
  0.692310;0.250000;,
  0.769230;0.250000;,
  0.846150;0.250000;,
  0.923080;0.250000;,
  1.000000;0.250000;,
  0.076920;0.375000;,
  0.000000;0.375000;,
  0.153850;0.375000;,
  0.230770;0.375000;,
  0.307690;0.375000;,
  0.384620;0.375000;,
  0.461540;0.375000;,
  0.538460;0.375000;,
  0.615380;0.375000;,
  0.692310;0.375000;,
  0.769230;0.375000;,
  0.846150;0.375000;,
  0.923080;0.375000;,
  1.000000;0.375000;,
  0.076920;0.500000;,
  0.000000;0.500000;,
  0.153850;0.500000;,
  0.230770;0.500000;,
  0.307690;0.500000;,
  0.384620;0.500000;,
  0.461540;0.500000;,
  0.538460;0.500000;,
  0.615380;0.500000;,
  0.692310;0.500000;,
  0.769230;0.500000;,
  0.846150;0.500000;,
  0.923080;0.500000;,
  1.000000;0.500000;,
  0.076920;0.625000;,
  0.000000;0.625000;,
  0.153850;0.625000;,
  0.230770;0.625000;,
  0.307690;0.625000;,
  0.384620;0.625000;,
  0.461540;0.625000;,
  0.538460;0.625000;,
  0.615380;0.625000;,
  0.692310;0.625000;,
  0.769230;0.625000;,
  0.846150;0.625000;,
  0.923080;0.625000;,
  1.000000;0.625000;,
  0.076920;0.750000;,
  0.000000;0.750000;,
  0.153850;0.750000;,
  0.230770;0.750000;,
  0.307690;0.750000;,
  0.384620;0.750000;,
  0.461540;0.750000;,
  0.538460;0.750000;,
  0.615380;0.750000;,
  0.692310;0.750000;,
  0.769230;0.750000;,
  0.846150;0.750000;,
  0.923080;0.750000;,
  1.000000;0.750000;,
  0.076920;0.875000;,
  0.000000;0.875000;,
  0.153850;0.875000;,
  0.230770;0.875000;,
  0.307690;0.875000;,
  0.384620;0.875000;,
  0.461540;0.875000;,
  0.538460;0.875000;,
  0.615380;0.875000;,
  0.692310;0.875000;,
  0.769230;0.875000;,
  0.846150;0.875000;,
  0.923080;0.875000;,
  1.000000;0.875000;,
  0.038460;1.000000;,
  0.115380;1.000000;,
  0.192310;1.000000;,
  0.269230;1.000000;,
  0.346150;1.000000;,
  0.423080;1.000000;,
  0.500000;1.000000;,
  0.576920;1.000000;,
  0.653850;1.000000;,
  0.730770;1.000000;,
  0.807690;1.000000;,
  0.884620;1.000000;,
  0.961540;1.000000;,
  0.000000;1.000000;,
  0.000000;0.750000;,
  0.125000;0.750000;,
  0.125000;1.000000;,
  0.250000;0.750000;,
  0.250000;1.000000;,
  0.375000;0.750000;,
  0.375000;1.000000;,
  0.500000;0.750000;,
  0.500000;1.000000;,
  0.625000;0.750000;,
  0.625000;1.000000;,
  0.750000;0.750000;,
  0.750000;1.000000;,
  0.875000;0.750000;,
  0.875000;1.000000;,
  1.000000;0.750000;,
  1.000000;1.000000;,
  0.000000;0.500000;,
  0.125000;0.500000;,
  0.250000;0.500000;,
  0.375000;0.500000;,
  0.500000;0.500000;,
  0.625000;0.500000;,
  0.750000;0.500000;,
  0.875000;0.500000;,
  1.000000;0.500000;,
  0.000000;0.250000;,
  0.125000;0.250000;,
  0.250000;0.250000;,
  0.375000;0.250000;,
  0.500000;0.250000;,
  0.625000;0.250000;,
  0.750000;0.250000;,
  0.875000;0.250000;,
  1.000000;0.250000;,
  0.062500;0.000000;,
  0.125000;0.000000;,
  0.187500;0.000000;,
  0.250000;0.000000;,
  0.312500;0.000000;,
  0.375000;0.000000;,
  0.437500;0.000000;,
  0.500000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;,
  0.000000;0.000000;;
 }
}