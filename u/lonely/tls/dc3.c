#include <ansi.h>
inherit ROOM;
string long_desc();
void create()
{
        set("short", GRN"点苍十九峰"NOR);
        set("long", (: long_desc :));
        set("resource/water", 1);
        set("outdoors", "大理");
        set("exits", ([
              "westup"    : __DIR__"dc2",
              "southdown" : __DIR__"diancang",            
        ]));
        set("coor/x",-340);
  set("coor/y",-420);
   set("coor/z",0);
   setup();
}

string long_desc()
{
        string desc;

        switch( random(6) ) {
        case 0: desc = 
"点苍山龙泉、玉局两峰，峰势平和，景色秀丽。峰中有‘龙泉’、
‘玉局’两泉，泉水清澈甘甜，是泡茶上品。两泉之水再加上山中无数小溪
水，成溪“绿玉”，流向大理城郊。\n";       
                break;
        case 1: desc =
"玉局、马龙两峰位于点苍山东，峰上绿林满覆，鸟兽出没，一派生机
勃勃的景象。“龙溪”从半山腰飞瀑而下，落入一深潭之中，瀑声若雷，宛
如龙吟。\n";               
                break;
        case 2: desc =
"马龙、圣应峰山势平坦，一溪曰“青碧”从中缓缓流出，于峰底平坡
上分为三条小溪，再又于山下‘圣应亭’侧相汇流向大理城郊。\n";      
                break;
        case 3: desc =
"圣应、佛顶两峰高矮相对，山间常年雾气弥漫，有如仙境。一溪流出，
名曰“莫残”，盘盘转转十几个弯后才向山下流去。\n";    
                break;
        case 4: desc =
"佛顶、马耳两峰形态怪异，峰中所生草木多为药材，时常有大理城中
的采药人来这里采集名贵草药。山上流下的“葶溟”溪据说也具奇效，常饮
百病不生、延年益寿。\n";      
                break;
        case 5: desc =
"点苍山东马耳、斜阳两峰前后并立，登上峰顶后大理城全貌尽收眼底，
是游人常来之地。“阳南”溪水从此流过，水流不急不缓，绕过山石流向大
理城郊。\n";       
                break;
        }

        return desc;
}