#include <ansi.h>
inherit ROOM;


void create ()
{
  set ("short","西湖");
  set ("long", @LONG
安南西湖，面积500公顷，是河内第一大著名风景区，古迹在这里也比较
集中，镇国寺、镇武观、金莲寺等，与国内古寺相仿。位于河内还剑湖西的
文庙，是古代王朝祀奉孔子的地方，文庙坐北朝南，红墙绿瓦，是一座典雅
的中国风格的建筑群。可以看出它与中国传统文化有着甚深的渊源。 
LONG);

  set("exits", ([ 
"east":__DIR__"center",        

       ]));
set("outdoors","annan");
  
  set("valid_startroom", 1);
  setup();
 
}
