inherit ROOM;
void create()
{
        set("short","般若台");
        set("long",@LONG
般若台是一个宽大的平台，是寺中弟子练习武艺的地方，台边
摆有木桩、梅花桩、沙袋、沙盆等练功设施和各种僧家武器。几名
年轻的出家弟子正在一旁相互切磋。
LONG);
        set("outdoors","天龙寺");
        set("exits", ([
                "west" : __DIR__"banruo",
              
        ]));
		set("objects",([
		__DIR__"npc/dizi-f" : 1,
	__DIR__"npc/dizi-m" : 1,
			]) );
        set("coor/x",-290);
  set("coor/y",-320);
   set("coor/z",40);
   setup();
}
