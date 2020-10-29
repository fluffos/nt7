inherit ROOM;

void create()
{
        set("short", "栈道");
        set("long", @LONG
栈道是通连接四川和中原的唯一道路，为了在险峻的山脉中打开
这条道路，不知道花费了多少人力物力，也不知死了多少人。这条路
是沿江而修成的，用大木桩钉在悬崖上，上面铺以木板，仅能过一两
个人。栈道因年久失修，走在上面摇摇晃晃的，好不危险。 
LONG );
        set("exits", ([
                  "east" : __DIR__"shudao5",
                  "west" : __DIR__"shudao7",
           ]));
        set("no_clean_up", 0);
        set("outdoors", "chengdu");
        set("coor/x", -15040);
	set("coor/y", -1830);
	set("coor/z", -60);
	setup();
        replace_program(ROOM);
}