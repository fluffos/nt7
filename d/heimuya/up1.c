// Room: carol/heimuya

#include <ansi.h>
inherit ROOM;

void check_trigger();
void on_board();
void arrive();
void close_passage();
int do_insert(string arg);
int do_push(string arg);
void goto_heimuya(object ob);

void create()
{
    set("short", "日月坪");
        set("long", @LONG
这里是半山的一片小土坪，离崖顶还有一段路途，可到这已经没
有路上去，面前是如境般的峭壁，仰头而望，但见崖顶依稀耸立着楼
阁，宛如仙境。可云烟缭绕，看不清晰。从悬崖上垂下一条绳索(rop
e)，看上去象是悬崖上下互通消息的工具，绳索的上面似乎隐约有一
个吊篮(basket)。悬崖的墙上似乎有一个匣子(xiazi) ，你似乎走入
一个雾宅，真不知如何是好。
LONG );

    set("exits", ([
        "eastdown" : __DIR__"shimen",
    ]));
    set("objects", ([
        CLASS_D("riyue") + "/zhang1" : 1,
    ]));

    set("outdoors", "heimuya");
    set("item_desc", ([
        "basket": "那是一个掉篮，看样子有些古怪。\n",
        "rope"  : "绳子就是绳子，可能是向上的工具。\n",
        "xiazi" : "这是一个匣子，好像可以按(push)下去。匣子的侧面有一个插孔。\n",
    ]));

    setup();
}

void init()
{
    add_action("do_insert", "insert");
    add_action("do_push", "push");
        add_action("do_float", "float");
        add_action("do_float", "piao");
}

void check_trigger()
{
    object room;

    if(!query("exits/enter") ) {
        if( !(room = find_object(__DIR__"basket")) )
            room = load_object(__DIR__"basket");
        if( room = find_object(__DIR__"basket") ) {
            if( query("insert_trigger", room) == 0){
                set("insert_trigger", 1, room);
                set("exits/enter", __DIR__"basket");
                set("exits/out", __FILE__, room);
                message("vision", "“叭”的一声，你手中的令牌已被折断，只见一个"
                        "掉篮(basket)从天而降，你不禁一怔！\n", this_object());
                set("item_desc", ([
                    "basket" : "这是一个掉篮，是传说中的交通工具。\n",
                ]));

                remove_call_out("on_board");
                call_out("on_board", 15);
            }
            else
                message("vision", "看样子你得等下拨儿。\n",this_object() );
        }
        else
            message("vision", "ERROR: basket not found\n", this_object() );
    }
}

void on_board()
{
    object room, me = this_player();
    if( !query("exits/enter") ) return;
    tell_object(me, HIG"只见掉篮缓缓向上，四周无限美好，"
                "你似乎置身于一处人间仙境无异。\n"NOR);

    if( room = find_object(__DIR__"basket") )
    {
        delete("exits/out", room);
    }
    delete("exits/enter");
    remove_call_out("arrive");
    call_out("arrive",20);
}

void arrive()
{
    object room;
    if( room = find_object(__DIR__"basket") )
    {
        set("exits/out", __DIR__"up2", room);
        message("vision", "噔的一声，你似乎一下从天上到了地上。\n",room );
    }
    remove_call_out("close_passage");
    call_out("close_passage", 20);
}

void close_passage()
{
    object room;
    if( room = find_object(__DIR__"basket") )
    {
        delete("exits/out", room);
        delete("insert_trigger", room);
    }
}

int do_insert(string arg)
{
    string dir;
    object ob;
    object me;

    me=this_player();

    if( !arg || arg=="" )   return 0;

    if( arg=="卡" )   arg = "card1";

    if( arg=="card1")
    {
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这样东西。\n");
        if( !query_temp("mark/cards", me) )
                set_temp("mark/cards", 1, me);
        if( query_temp("mark/cards", me) == 4 )
        {
                delete_temp("mark/cards", me);
                destruct(ob);
                check_trigger();
        }
        else    {
                addn_temp("mark/cards", 1, me);
                message("vision", "噔的一声，你看到掉篮向下一节。\n",me );
        }
    }
    else
    {
        if( !objectp(ob = present(arg, me)) )
                return notify_fail("你身上没有这样东西。\n");
        else    return notify_fail(ob->name() + "好像跟插孔不合，怎么也插不进去。\n");
    }
    return 1;
}

int do_push(string arg)
{
    object ob, myenv;
    ob = this_player();

    if( !arg || arg != "xiazi" )
         return notify_fail("你要 push 什么？\n");

    if( query("family/family_name", ob) == "日月神教" )
    {
         message_vision("$N把匣子按了几下，只听“吱扭吱扭”几声，从崖上落下一个大吊篮。\n", ob);
         message_vision("$N一弯腰进了吊篮，吊篮缓缓地绞上崖去......\n", ob);
         myenv = environment(ob);
         ob->move (__DIR__"basket");
         call_out("goto_heimuya", 10, ob);
         return 1;
    }
    else
         message_vision("$N把匣子按了几下，但好像没什么作用。\n",ob);
    return 1;
}

void goto_heimuya(object ob)
{
    tell_object(ob , "你眼前一亮，一幢幢白色建筑屹立眼前，霎是辉煌。\n");
    ob->move(__DIR__"chengdedian");
}

int do_float()
{
        object me;

        me = this_player();

        if (me->query_skill("juechen-shenfa", 1) < 180)
        {
                message_vision("$N遥望山崖，沉思良久，叹了口气。\n", me);
                return 1;
        }

        if( query("neili", me)<100 )
        {
                tell_object(me, "你的内力不够，还是休息一下再说吧。\n");
                return 1;
        }

        addn("neili", -80, me);

        message_sort(HIC "\n$N" HIC "深深纳入一口气，蓦地一飞而起，朝"
                     "山崖上飘去。\n\n" NOR, me);

        me->move(__DIR__"shanya3");
        tell_object(me, "你顺着崖壁飘上了黑木崖。\n");
        message("vision", HIC "\n忽听一声清啸由远及近，" + me->name() +
                          HIC "顺着崖壁飘然而上，落定身形。\n" NOR,
                          environment(me), ({ me }));
        return 1;
}
