// Room in 高丽
inherit ROOM;
void create()        
{
        set("short", "甲板");
        set("long", @LONG        
这里是战船的甲板。有几名水手不时从你身旁走过，看来都很忙碌。
放眼望去，大海碧波万倾，一望无际，不禁想驾驶这艘战船，来闯荡一番。
LONG
        );
set("outdoors", "gaoli");
set("exits", ([
                "north" : __DIR__"shatan2",
                "enter":__DIR__"chuancang",
        ]));
      set("objects",([
          __DIR__"npc/shuishou":1,
          ]));
       setup();
        replace_program(ROOM);
}        
