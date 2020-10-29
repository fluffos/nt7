inherit ROOM;

void create()
{
        set("short", "琴心小院");
        set("long", @LONG
穿过月洞门，便是一座看起来非常普通的小小的院落，两旁修竹
姗姗，花径鹅卵石上生满青苔，显得平素少有人行。花径通到三间石
屋之前。屋前屋后七八株苍松夭矫高挺，遮得四下里阴沉沉的。院子
里没有什么摆设，只有几堆干木柴(wood)放在角落里，其中有一捆特
别引人注目。 
LONG );
        set("exits", ([
                "south" : __DIR__"yuedong",
                "enter" : __DIR__"xiaowu",
        ]));

        set("item_desc",([
                "wood" : "一大堆干柴，其中有一捆的颜色比较特别。\n",
        ]));
        set("objects", ([
                __DIR__"npc/shi" : 1,
        ]));

        set("outdoors", "meizhuang");

        setup();
}

void init()
{
        add_action("do_pull", "pull");
        add_action("do_unlock", "unlock");
        if (present("ding jian", environment(this_player())))
                delete("exits/east");
}
int do_unlock(string arg)
{
        object ob;
        if (query("exits/east"))
                return notify_fail("这扇门已经是打开的。\n");
        if (!arg || (arg != "men" && arg != "east"))
                return notify_fail("你要打开什么？\n");
        if (!(ob = present("tong yaoshi", this_player())))
                return notify_fail("你不会撬锁。\n");
        set("exits/east", "/d/meizhuang/mishi2");
        message_vision("$N把红玉钥匙放进门的凹陷处, 东边的一扇门无声的打开了。\n", this_player());
        destruct(ob);
        return 1;
}
int do_pull(string arg)
{
        object me , ob;
        me = this_player();
        if (arg == "wood" && !present("sea-wood", me) && query("weapon_count") >= 1)
        {
                addn("weapon_count", -1);
                ob=new("/d/meizhuang/obj/sea-wood");
                ob->move("/d/meizhuang/xiaoyuan");
                message_vision("$N在木柴堆里拨弄着, 一根剑形的木棒掉了出来.\n", me);
                return 1;
        }
        else {
                message_vision("$N找了半天,也没有发现什么特别的东西.\n", me);
                return 1;
             }
}
int valid_leave(object me, string dir)
{
        object shi;

        if (dir != "enter" ||
            ! objectp(shi = present("shi lingwei", this_object())))
                return ::valid_leave(me, dir);

        return shi->permit_pass(me, dir);
}