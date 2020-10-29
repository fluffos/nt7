// for feng_obj.c yu_obj.c lei_obj.c dian_obj.c

#include "hj_settings/room_amount_hj.h"


void setme( int iii )
{
//    if( iii == 99 )
//        iii = random(3);
// 其他文件内使用这个方式随机  set.

    set( "iii", iii );

    set_name(names[ iii ], ({ids[ iii ]}));
    set_weight(100);
    if( !query( "host_id") ) set("host_id","----");
    set("hj_game/obj",my_mark);
    set("msg", MAG"半空中忽地掉下一件物事，像是一件宝物！\n"NOR);
    if( iii !=3 )
        set("long", longs[ iii ]+query("host_id")+"\n");
    else set("long", longs[ iii ]+"\n");
    set("unit", units[ iii ]);
    set("value", 1);  // 该物件扔下后不会消失。

    set("pivotal",pivotal[ iii ] );
    set("no_refresh", 1);  // 有此设置时，在 no_clean_up 的房间内，不会被刷新掉！

    remove_call_out( "checking" );
    remove_call_out( "delete_me" );

    if( query("iii") < 3 ) call_out( "checking", 3 );
}

void create()
{
    setme( random(3) );
    setup();
}

void init()
{
    add_action("do_zuhe","zuhe");
}

// 如果该OBJ的隶属玩家不存在或已退出游戏，本OBJ清除。
void checking()
{
    object my_host;

    if( !environment( this_object() ) ) return;

    my_host=find_player(query("host_id"));
    if( !my_host || query_temp("hj_hp", my_host)<1 || !query_temp("huanjing", my_host) )
    {
        remove_call_out("delete_me");
        call_out("delete_me",1);
    }

    else
    {
        remove_call_out("checking");
        call_out("checking",1);
    }
}

int do_zuhe(string arg)
{
    object ob,me,need1,need2,need3,ok_obj;

    if( !query("room_mark", environment(this_player())) && !wizardp(this_player()) )
        return 0;

    me=this_player();
    ob=this_object();

    if( !arg || arg != query("id", ob) || !query_temp("huanjing", me) || 
       query_temp("huanjing", me) != "start" || !query_temp("hj_hp", me) || 
       query_temp("hj_hp", me)<1 )
        return 0;

    if( query("id", ob) == ids[3])return 0;

    if( query("pivotal", ob) != "yes" )
        return notify_fail(query("name", ob)+"不是最重要的部分，不能由它开始组合。\n");

    need1=ob;
    need2=present(ids[1],me);
    need3=present(ids[2],me);

    if(!need1 || !need2 || !need3)
        return notify_fail("所有的部分还未找全呢。\n");

    message_vision(my_color+"$N"NOR""+my_color+"取出"+names[0]+my_color+"、"+names[1]+my_color+"和"+names[2]+my_color+"，把它们组合成了"+my_msg+"的宝物——"+names[4]+my_color+"！\n"NOR,me);

    ok_obj=new(base_name(this_object()));

    if(!ok_obj) return notify_fail(HIR"该文件路径或文件名已经更改，无法继续游戏。请联系巫师获得帮助并申请奖励。\n");

    if( query("host_id", need1) != query("id", me) || 
        query("host_id", need2) != query("id", me) || 
        query("host_id", need3) != query("id", me) )
    {
        ok_obj->setme(3);
        set("fake", "yes", ok_obj);
    }

    else
    {
        set("host_id",query("id",  me), ok_obj);
        set("this_time_mark",query_temp("this_time_mark",  me), ok_obj);
        ok_obj->setme(4);
        set_temp("hj_find_ok", "yes", me);
    }

    ok_obj->move(me);

    destruct(need2);
    destruct(need3);
    destruct(need1);  // 本文件最后清除。
    return 1;
}

void delete_me()
{
    if( !environment( this_object() ) ) return;
    message_vision("$N忽地一闪光，消失不见了。\n",this_object());
    destruct(this_object());
}