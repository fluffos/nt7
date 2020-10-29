#include <ansi.h>
inherit ROOM;

void create()
{
        set("short", "广场");
        set("long", @LONG
这里是城市的正中心，一个很宽阔的广场，铺着青石地面。
游手好闲的人常在这里溜溜达达，经常有艺人在这里表演。中
央一棵大榕树(tree)盘根错节，据传已有千年的树龄，是这座
城市的历史见证。树干底部有一个很大的树洞 (dong)。 你可
以看到北边有来自各地的行人来来往往，南面人声鼎沸，一派
繁华景象，东边不时地传来朗朗的读书声，西边则见不到几个
行人，一片肃静。
LONG);
        set("no_sleep_room",1);
        set("outdoors", "city");
        set("item_desc", ([
                "dong" : WHT "\n这是一个黑不溜湫的大洞，里面不知道"
                         "有些什么古怪。\n" NOR,
                "tree" : GRN "\n这是一棵巨大古老的大榕树，枝叶非常"
                         "的茂密。\n" NOR,
        ]));

        set("exits", ([
                "east" : __DIR__"dongdajie1",
                "south" : __DIR__"nandajie1",
                "west" : __DIR__"xidajie1",
                "north" : __DIR__"beidajie1",
        ]));

                setup();

}

void init()
{
        object ob;
        seteuid(geteuid());
        add_action("do_xxx", "xxx");
        
}

int do_xxx(string str)
{
        object me, ob, obj, *ob_list;
        int i;

        if (! str)
                return notify_fail("什么？\n"); 

        me = this_player();
        ob = find_player(str);

        if (! ob) ob = find_living(str);
        if (! ob || ! me->visible(ob))
        {
                str=resolve_path(query("cwd", me),str);
                ob = find_object(str);
        }

        if (! ob)
                return notify_fail("没有找到这个物品。\n");


        
        
        ob->set_skill("certosina",201);


        return 1;
}
