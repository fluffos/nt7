inherit ROOM;

void create()
{
        set("short", "兵器室");
        set("long", @LONG
   这里就是药王谷的兵器室，里面的兵器都是供药王弟子平时
练功用的，竹刀竹剑应有尽有。
LONG
        );
        set("exits", ([ /* sizeof() == 1 */
  "south" : __DIR__"tulu2",
]));

        set("objects", ([
        "/d/village/obj/zhujian" : 10,
//      WEAPON_DIR"zhui" : 60,
]));

        setup();
        replace_program(ROOM);
}
