// qiankun.c
// redl 2015/10

#include <ansi.h>
inherit F_CLEAN_UP;

int help(object me);

int do_beep(object obj)
{
        if (! obj) return 1;
        tell_object(obj, "\a", 0);
        return 1;
}

void bp(object obj)
{
        call_out("do_beep", 1, obj);
        call_out("do_beep", 2, obj);
        call_out("do_beep", 3, obj);
        call_out("do_beep", 4, obj);
}

int main(object me, string arg)
{
                object room, qkroom;
                string roompath;
                string ownid, myid;
                string* guests;
                object guest;
        string file;
        string str;
        object *obs, cha;
        int tmpi, r_type = 0;
 
        if (!arg ) return help(me);
                room = environment(me);
        if (!room) return 0; 
        roompath = base_name(room);
                if( sscanf(roompath, "/d/register/%*s") ) return notify_fail("你还没有出生呢，不能施展！\n");
                if( sscanf(roompath, "/d/newbie/%*s") ) return notify_fail("你在古村中，不能施展！\n");
        if (me->is_ghost()) return notify_fail("等你还了阳再说吧。\n"); 
        if (me->is_in_prison()) return notify_fail("你正在做牢呢。\n");
        if( query("doing", me) ) return notify_fail("你还想干什么？！\n");

                //召唤茶宠功能
                if (arg == "alarm" || arg == "help") {
                        if (room->is_qkroom()) return notify_fail("你在乾坤棋盘里无法使用这个功能。\n");
                        if (query("qkhelpkill_time", me) >= time()) return notify_fail("你正在召唤茶宠中。\n");
                        myid = query("id", me);
                        file = "/temp/qroom/" + myid + ".c";
                        qkroom = get_object(file);
                        if (!qkroom) return notify_fail("你尚未进入过乾坤棋盘。\n"); 
                                obs = all_inventory(qkroom);
                                foreach (cha in obs) {
                                        if (query("id", cha) == "cha chong") {
                                                cha->do_helpkill(me, cha);
                                                r_type = 1;
                                                break;
                                        }
                                }
                        set("qkhelpkill_time", time()+1, me);
                        me->start_busy(2);      
                        if (!r_type) write("你的棋盘里目前没有待命的茶宠。\n"); 
                        return 1;
                }
                
        if (me->is_busy()) return notify_fail("你正忙著呢。\n");
        me->start_busy(1);

                //空间变幻功能
                if (present("biao huo", me)) return notify_fail("你身上带著镖银，不能施展！\n");
        if (me->is_fighting()) return notify_fail("你现在正在战斗！\n"); 
                if( query_temp("warquest/party", me) ) return notify_fail("你还想在战争中使用？！\n");
        if( query("no_magic", room) || query_temp("in_pkd", me) ) return notify_fail("你发现这里不可以施展！\n"); 
                if (sscanf(roompath,"%*s/dongtian/%*s")) return notify_fail("洞天隔绝了空间！\n");
                if (sscanf(roompath,"%*s/teleport/%*s")) return notify_fail("福地隔绝了空间！\n");
                if (sscanf(roompath,"/f/%*s")) return notify_fail("你发现这里不可以施展！\n");
                
                if (sscanf(arg, "%s %s", arg, str) == 2) {
                        if (!room->is_qkroom()) return notify_fail("你现在没有身处乾坤棋盘内，无法使用这个功能。\n");
                        if (!sscanf(roompath,"%*s/qroom/%s", ownid)) return help(me);
                        if (query("id", me) != ownid) return notify_fail("这个棋盘里你做不了主。\n"); 
                        if (arg == "add") {
                                guests = query("guests", room);
                                if (!guests || !sizeof(guests)) guests = ({});
                                if (sizeof(guests) >= query("qiankunqipan/limit_guest", me)) return notify_fail("你的乾坤白棋子数量不足。\n"); 
                                if (member_array(str, guests)<0) {
                                        guests += ({str});
                                        set("guests", guests, room);
                                }
                                message_vision(NOR YEL "$N" NOR YEL  "捻起一枚白棋落在棋盘上，棋子上慢慢闪现一个深痕\"" + str + "\"。\n" NOR, me);
//                              guest = find_player(str);
//                              if (guest && objectp(guest)) {
//                                      tell_object(guest, NOR HIG "你识海里传来一阵波动，原来是" + me->name() + NOR HIG "邀请你进入乾坤棋盘。" NOR HIK " ( 在合适的位置输入：qiankun " + ownid + " )\n" NOR);
//                                      bp(guest);
//                              }
                                return 1;
                        }
                        else if (arg == "clear") {
                                guests = query("guests", room);
                                if (!guests || !sizeof(guests)) guests = ({});
                                guest = find_player(str);
                                if (guest && objectp(guest) && environment(guest)==room) {//驱逐
                                        message_vision(NOR YEL "$N" NOR YEL  "伸出手指一点，一枚棋子把"NOR YEL "$n" NOR YEL "压落到了虚空。\n" NOR, me, guest);
                                        if (query("startroom", guest)==roompath) delete("startroom", guest);
                                        guest->move(VOID_OB);
                                        guest->save();
                                        if( query("doing", guest) ) "/cmds/usr/scheme.c"->cancel_schedule(guest);
                                }
                                if (member_array(str, guests)<0 && query("guesttmp", room)!=str) {
                                        write("你没有邀请过这个人。\n"); 
                                        return 1;
                                }
                                guests -= ({str});
                                set("guests", guests, room);
                                if (query("guesttmp", room)==str) delete("guesttmp", room);
                                message_vision(NOR YEL "$N" NOR YEL  "捻起一枚写着\"" + str + "\"的白棋子收回怀里。\n" NOR, me);
                                if (query("guesttmp", room) && member_array(query("guesttmp", room), guests)<0) guests += ({query("guesttmp", room)});
                                if (sizeof(guests))
                                        tell_object(me, NOR "你目前邀请的客人有："+implode(guests, ",")+"。\n" NOR);
                                else
                                        tell_object(me, NOR "你目前没有邀请任何客人。\n" NOR);
                                return 1;
                        }
                        return help(me);
                } else {
                        if (arg == "here") {
                                if (query("qiankunqipan/limit_guest", me) < 4) return notify_fail("你的乾坤黑棋子数量不足。\n"); 
                                if (sscanf(roompath,"/d/%*s")) r_type = 1;
                                if (sscanf(roompath,"/data/room/%*s")) r_type = 2;
                                if (room->is_qkroom()) return notify_fail("你想在乾坤棋盘里嵌套乾坤棋盘？脑洞真大...\n"); 
                                if (!query("no_fight", room)) return notify_fail("你不能在非安全房间放置黑棋。\n"); 
                                if (query("valid_startroom", room)) r_type = 0;
                                if (room->is_chat_room()) r_type = 0;
                                if (!r_type) return notify_fail("你不能在这里放置黑棋。\n"); 
                                file = "/temp/qroom/" + query("id", me) + ".c";
                                if (file_size(file) < 1) return notify_fail("你尚未进入过乾坤棋盘。\n"); 
                                qkroom = get_object(file);
                                if (!qkroom) return notify_fail("你的乾坤棋盘错误。\n"); 
                                set("to_down", roompath, qkroom);
                                message_vision(NOR YEL "$N" NOR YEL  "抛出枚本命黑棋子扔在地上，棋子慢慢地侵入了土中，逐渐消失不见。\n" NOR, me);
                                tell_object(me, NOR "你可以从自己的乾坤棋盘内直接降临这里了。\n" NOR);
                                return 1;
                        }
                        else if (arg == "clear") {
                                if (!room->is_qkroom()) return notify_fail("你现在没有身处乾坤棋盘内，无法使用这个功能。\n");
                                if (!sscanf(roompath,"%*s/qroom/%s", ownid)) return help(me);
                                if (query("id", me) != ownid) return notify_fail("这个棋盘里你做不了主。\n"); 
                                obs = all_inventory(room);
                                foreach (object ep in obs) {//驱逐
                                        //write(ep->name() + "\n");
                                        if (!playerp(ep)) continue;
                                        if (ep == me) continue;
                                        message_vision(NOR YEL "$N" NOR YEL  "伸出手指一点，一枚棋子把"NOR YEL "$n" NOR YEL "压落到了虚空。\n" NOR, me, ep);
                                        if (query("startroom", ep)==roompath) delete("startroom", ep);
                                        ep->move(VOID_OB);
                                        ep->save();
                                        if( query("doing", ep) ) "/cmds/usr/scheme.c"->cancel_schedule(ep);
                                }
                                delete("guests", room);
                                delete("guesttmp", room);
                                message_vision(NOR YEL "$N" NOR YEL  "把棋盘上所有的白棋子收回怀里。\n" NOR, me);
                                tell_object(me, NOR "你目前没有邀请任何客人。\n" NOR);
                                return 1;
                        }
                        else {
                                if (room->is_qkroom()) {
                                        if (!sscanf(roompath,"%*s/qroom/%s", ownid)) return help(me);
                                        if (query("id", me) != ownid) return notify_fail("这个棋盘里你做不了主。\n"); 
                                        if (query("id", me) == arg) return notify_fail("你到外面再直接使用这指令吧。\n"); 
                                        guest = find_player(arg);
                                        if (guest && objectp(guest)) {
                                                if (environment(guest)==room) return notify_fail("这人现在不就在眼前么？\n"); 
                                                tell_object(guest, NOR HIG "你识海里传来一阵波动，原来是" + me->name() + NOR HIG "邀请你进入乾坤棋盘。" NOR HIK " ( 在合适的位置输入：qiankun " + ownid + " )\n" NOR);
                                                bp(guest);
                                        }
                                        set("guesttmp", arg, room);                                     
                                        message_vision(NOR YEL "$N" NOR YEL  "捻起一枚白棋落在棋盘上，棋子上慢慢闪现一个淡影\"" + arg + "\"。\n" NOR, me);
                                        tell_object(me, NOR "你临时邀请了\"" + arg + "\"进入这里。\n" NOR);
                                        return 1;
                                } else {
                                        file = "/temp/qroom/" + arg + ".c";
                                        //if (file_size(file) < 1) return notify_fail("对方尚未进入过乾坤棋盘。\n"); 
                                        qkroom = get_object(file);
                                        if (!qkroom) return notify_fail("对方尚未进入过乾坤棋盘。\n"); 
                                        guests = query("guests", qkroom);
                                        if (!guests || !sizeof(guests)) guests = ({});
                                        if (member_array(query("id", me), guests)<0 && query("guesttmp", qkroom)!=query("id", me) && arg!=query("id", me)) return notify_fail("对方未邀请你进入乾坤棋盘。\n"); 
                                        if (query("guesttmp", qkroom)==query("id", me)) delete("guesttmp", qkroom);
                                        message_vision(NOR YEL "一片青霞飞来，转眼变成白洞漩涡，把" NOR YEL "$N" NOR YEL  "吞下消失了。\n" NOR, me);
                                        me->move(qkroom);
                                        message_vision(NOR YEL "天上青霞舒卷，现出道空间漩涡，一张一吐，" NOR YEL "$N" NOR YEL  "从里面滚落出来。\n" NOR, me);
                                        return 1;
                                }
                        }
                }

                return help(me);
        return 1;
}

int help(object me)
{
 write(@HELP
 《乾坤棋盘大召唤》
指令格式 : qk|qiankun
  主人在乾坤棋盘里邀请人的指令为 < qk sb > ，sb是临时客人id，同时最多一位。
  主人在乾坤棋盘里邀请人的指令为 < qk add sb > ，sb是客人id，能一直保持邀请。
  主人在乾坤棋盘里清除白棋指令为 < qk clear sb> ，取消对某客人的邀请，不带sb参数则全部取消。
  主人在棋盘外设置黑棋位置指令为 < qk here > ，黑棋只有1颗，只能设置在寻常的安全房间内。
  客人在棋盘外呼应被召唤的指令为 < qk sb > ，sb是主人id。
  主人在棋盘外召唤茶宠护法指令为 < qk help > ，参数help或者alarm需要先利用乾坤符昭收伏敌人为茶宠。
由于乾坤召唤可能导致很多任务流程的改变，必须算是道家的珍稀秘术。
一次性购入的代价不菲，参见ntstore look qiankunqi。
HELP
    );
    return 1;
}



