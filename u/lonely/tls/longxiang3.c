inherit ROOM;

void create()
{
        set("short", "西练武场-龙象台");
        set("long",@LONG
龙象台是一个宽大的平台，是寺中僧侣练习武艺的地方，台边
摆有木桩、梅花桩、沙袋、沙盆等练功设施和各种僧家武器。几个
年轻的僧人正在一旁相互切磋。
LONG);
        set("outdoors","dali");
        set("exits", ([
               "northup" : __DIR__"longxiang1",
           
       	]));
        set("coor/x",-400);
  set("coor/y",-330);
   set("coor/z",20);
   setup();
}
