#include <ansi.h>

inherit ROOM;

void create()
{
        set("short","悬崖底");
        
        set("long", @LONG
这里是衡山悬崖底，四周都被悬崖绝壁包围着，举目一望，只见
云雾深锁，崖壁陡峭，直没天际，几只老鹰在上空不断的盘旋。绝壁
上垂下几根树藤(teng)，看来可以顺着这里爬上崖顶。耸立在你面前
是一棵巨大的古树(tree)，刚才你幸好抓住了这棵树的树枝，不然早
就粉身碎骨了。你到处看了看，这里似乎没有其他路可走。
LONG );

        set("item_desc",([
              "teng": HIG "\n这根树藤看起来很结实，可以用它爬(climb)上悬崖。\n" NOR,
              "tree": YEL "\n参天古树，树干粗大结实，但是有根树枝已经被折断了。\n" NOR,
        ]));        
           
        set("objects",([
              "/clone/quarry/tu" : 7,        
        ]));

        set("outdoors","henshan");

        setup();
}


void init()
{              
        add_action("do_climb",({"climb","pa"}));
        
}

int do_climb(string arg)
{
        object me, here, zigai;
        string msg;
        int qi;

        me = this_player();
        qi=query("qi", me);
        
        if (! arg || (arg != "teng" && arg != "tree"))
                return notify_fail("你想往哪儿爬？\n");
        
        if ( !here = find_object(__DIR__"xuanyandi"))
                here = load_object(__DIR__"xuanyadi");
        if ( !zigai = find_object(__DIR__"zigai"))
                zigai=load_object(__DIR__"zigai");

        if ( arg == "teng")
        {
                 msg = HIG "\n$N" HIG "拉着树藤往峭壁上爬去。\n"NOR;
        
                if(qi < 100)
                {
                        msg += HIM "\n$N " HIM "体力不知，从峭壁上摔了下来。\n" NOR;
                        message_vision(msg, me);
                        me->unconcious();
                        return 1;
                }

                message_vision(msg, me);
                message("vision",HIG "\n"+me->name()+"从峭壁下面爬了上来。\n", zigai, me);
                me->move(zigai);

                return 1;

        }

        me->move(__DIR__"ontree");

        return 1; 
        
}

