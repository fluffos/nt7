inherit ROOM;

void create()
{
        set("short", "龙象台");
        set("long",@LONG
龙象台是一个宽大的平台，是寺中俗家弟子练习武艺的地方，
台边摆有木桩、梅花桩、沙袋、沙盆等练功设施和各种僧家武器。
几名年轻的俗家弟子正在一旁相互切磋。
LONG);
        set("outdoors","天龙寺");
        set("exits", ([
                "eastdown" : __DIR__"3wg",
                "west" : __DIR__"longxiang4",
	        "northup" : __DIR__"longxiang2",
                "southdown" : __DIR__"longxiang3",
           
       	]));
       
        set("coor/x",-400);
  set("coor/y",-320);
   set("coor/z",30);
   setup();
}
