// caidi1.c 盘龙居菜地

//** inherit PRIVATE_ROOM;
inherit ROOM;                                   /* EXAMPLE */

void create()
{
        set("short", "菜地");                      /* EXAMPLE */
//**    set("short", "ROOM_NAME菜地");
        set("long", @LONG
这片菜园子几畦地里种了一些时鲜蔬菜。另外有几个木桩搭起的
菜架子，供一些爬藤的蔬菜生长，不过你举目看去，老大的一片菜园
子，居然疏疏落落的没有几棵菜。
LONG );

        set("default_long", "这片菜园子几畦地里种了一些时鲜蔬菜。另外有几个木桩搭起的"   /* EXAMPLE */
                            "菜架子，供一些爬藤的蔬菜生长，不过你举目看去，老大的一片菜园"   /* EXAMPLE */
                            "子，居然疏疏落落的没有几棵菜。"); /* EXAMPLE */

        set("exits", ([
                "south" : __DIR__"huayuan",
        ]));
        set("outdoors", "OUTDOORS");
        set("no_sleep_room", 1);
        setup();

//**    set("room_owner", "ROOM_OWNER");
//**    set("room_name", "ROOM_NAME");
//**    set("room_id", "ROOM_ID");
//**    set("room_owner_id", "ROOM_OWNER_ID");
//**    set("room_position", "ROOM_POSITION");
}
