// Room: /city/kedian4.c 
// SMALLFISH 1995/12/04 
 
#include <ansi.h> 
#include <room.h>  

inherit ROOM;

int is_chat_room() { return 1; }  

int give_cigarette()
{
        object *obs, op;
        string idstr, *usr=({});
        object ob; 
        int i, m;
        
        remove_call_out("give_cigarette");
                "/u/redl/obj/cigarette_c"->do_save(("/u/redl/obj/cigarette_c"->do_load()) + 100000 + random(300000)); 
        obs = all_inventory(); 
        if (sizeof(obs) > 0) 
        { 
                if (arrayp(query_temp("objects"))) obs -= query_temp("objects"); 
                obs = filter_array(obs, (: $1->is_user() :)); 
                if (sizeof(obs) > 0) 
                { 
                
                        obs = obs[0..<1]; 
                      foreach (ob in obs) {
                               
                             if (query("online_time", ob) > 604800) usr += ({query("id", ob)}); //86400*7天
                                //destruct(ob); 
                        }
                } 
        } 
        //write("总共：" + to_string(sizeof(usr)) + "人\n");
//      for(i = sizeof(usr)-1; i > -1; i--) {
//              write("第" + to_string(i) + "人是" + usr[i] + "\n");
//      }
        m = sizeof(usr);
        if (m) for(i = m/3; i > 0; i--) {
                idstr = usr[random(sizeof(usr))];
                if (idstr) {
                        //write("发给" + to_string(idstr) + "\n");
                        usr -= ({idstr});
                        op = find_player(idstr); 
                        if (wiz_level(op) < wiz_level("(wizard)")) {
                                tell_object(op, YEL + "小常子屁颠屁颠地跑过来，悄悄递给你一包烟然后跑开了。\n" + NOR); 
                                new("/u/redl/obj/cigarette")->move(op);
                                if (!random(4)) { //每个钢镚等于0.66泥潭币
                                      tell_object(op, YEL + "你接过香烟一看，里面还夹着枚硬硬的钢镚。\n" + NOR);  
                                      new("/u/redl/npc/obj/penny")->move(op); 
                                }
                        }
                }
        }
        call_out("give_cigarette", 7200 + random(3600));
        return 1;
}

int no_flood()
{
        write("你别在这里刷屏嘛，到down去折腾好不？\n");
        return 1;
}

int do_push(string arg)
{
        object target, me, room;

        me=this_player();
        if( !wizardp(me) && query("viremploy/job", me) != "新手导师" )  return 1;
                
         if( !arg || arg==query("id", me) ) {
                write("你要把谁推进猪圈里？\n" NOR); 
                return 1;
         }

        target = find_player(arg); 
        
        if( !objectp(target) ) { 
                write("无此玩家。\n" NOR); 
                return 1; 
        } 
        if( environment(target)!=this_object() ) { 
                write("此玩家不在这里。\n" NOR); 
                return 1; 
        } 
        if( wiz_level(me) <= wiz_level(target) ) { 
                write("你权限不够。\n" NOR); 
                return 1; 
        } 

        message_vision(YEL"$N狠狠一推$n说道：“别刷屏了好不...”\n$n一个踉跄，骨碌骨碌地往下方滚去。\n"NOR, me, target);
        tell_object(target, "目前你将忙碌五分钟，如果是单纯想发呆，请set keep_idle\n"NOR); 
        room = find_object("/d/city/tree2");
        tell_room(room, YEL+query("name", target)+NOR+YEL"从上面骨碌骨碌地滚了下来！\n"NOR);
        target->move(room); 
        target->start_busy(300);
        return 1;
}

void create() 
{
        set("short", "大隐阁");
        set("long", @LONG
这里是建造在扬州大榕树上的空中楼阁，又名大隐阁，迁客骚人汇聚
之地。靠墙竖着一块留言板，上面密密麻麻写着许多过往客人留下的手迹。
LONG );

        set("no_fight", 1);
        set("no_drift", 1);
        set("no_steal", 1);
        set("no_beg", 1);
        set("valid_startroom", 1);
        set("no_sleep_room",1); 
        set("no_rideto", 1);
        set("no_flyto", 1);
        set("no_smoke", 1);
        //set("trans_msg_to", 1);
        set("exits", ([
                  "down"   : "/d/city/tree2",
                      "north"   : "/u/redl/teleport/teleport", 
                  "east"   : "/d/city/qiyuan/xxzl1",
                  "south"   : __DIR__"swing",
                  "service":"/d/city/advice/advice",
                  "wumiao":"/d/city/wumiao",
   "west" : "/u/redl/school/gate",  
        ]));
        set("objects", ([
//                 "/adm/npc/huangdaxian" : 1,
        ]));

        set("coor/x", 0);
        set("coor/y", 0);
        set("coor/z", 0);
        setup();
        "/clone/board/kedian_b"->foo();
                call_out("give_cigarette", 7200 + random(3600));
}


void init()
{
        add_action("do_push", "push"); 
        add_action("no_flood", "whistle"); 
        add_action("no_flood", "rideto"); 
        add_action("no_flood", "take");
        add_action("no_flood", "put");
        add_action("no_flood", "store");
                add_action("no_flood", "summon"); 
                add_action("no_flood", "wield"); 
                add_action("no_flood", "unwield"); 
                add_action("no_flood", "remove"); 
                add_action("no_flood", "wear"); 
                add_action("no_flood", "equip"); 
                add_action("no_flood", "souxun"); 
        // 既然已经有了push功能，其他的就不用了，让新导来控制刷频吧
/*
        add_action("no_flood", "get");
        add_action("no_flood", "give");
        add_action("no_flood", "drop");
        add_action("no_flood", "eat");
        add_action("no_flood", "drink");
*/

        if( this_player()->is_warcraft() )
        {
                call_out("destruct_ob", 1, this_player());
                return;
        }
        if( !wizardp(this_player()) )
        {
                this_player()->start_busy(5);
                tell_object(this_player(), HIC "你来到聊天室，只好把别的事暂时停下来了。\n" NOR);
        }
}

int destruct_ob(object ob)
{
        object own;
        if( !objectp(ob) ) return 1;
        //msg(HIK "突然一个身影闪过，"+query("name", ob)+HIK"被一脚踢飞出去。\n" NOR, ob, 0, 1);
        own = find_player(query("owner", ob));
        if (!own || !objectp(own) || !playerp(own)) return 1;
        tell_object(own, HIK "突然一个身影闪过，"+query("name", ob)+HIK"被一脚踢飞出去。\n" NOR);
        destruct(ob);
        return 1;
}




#include <transmsg.h>



