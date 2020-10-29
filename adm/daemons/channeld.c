// This program is a part of NT MudLIB

#define PLAYER               0
#define TEACHER              1
#define IMMORTAL             2
#define WIZARD               4

#define CHAT                 (1<<0)        //闲聊
#define RUMOR                (1<<1)        //谣言
#define MESS                 (1<<2)        //江湖
#define WIZ                  (1<<3)        //巫师
#define SYS                  (1<<4)        //系统
#define NCH                  (1<<5)        //监测
#define NEWS                 (1<<6)        //新闻
#define G_WIZ                (1<<7)        //国际巫师
#define OTHER                (1<<9)        //其他
#define AD                   (1<<10)       //广告
#define FAMILY               (1<<11)       //门派
#define WAR                  (1<<12)       //战场
#define PARTY                (1<<14)       //帮派
#define STOCK                (1<<15)       //股票
#define AUC                  (1<<16)       //拍卖
#define DEBUG                (1<<17)       //测试
#define COMBAT               (1<<18)       //战斗
#define GROUP                (1<<19)       //队伍
#define DT                   (1<<20)       //洞天

#define SPECIAL_NPC     ({ "/adm/npc/youxun" })

#include <ansi.h>
#include <mudlib.h>
#include <net/dns.h>
#include <net/macros.h>
#include <localtime.h>

inherit F_DBASE;

#define DEFAULT_REFUSE  ( NCH | OTHER | AD )

class channel_class
{
        int level, number;
        string msg;
        mapping extra;
}

mapping channels;
mapping users;
nosave int water_number;
mapping query_chann() { return channels; }

nosave string msg_log;
nosave int log_from;


int krok_award = time();
int krok_top1 = 0;
int krok_top2 = 0;
string krok_id1,krok_id2;

string *info =
({
    ({
        WAR,
        "war",
        PLAYER,
        BLU "【"HIB"战"NOR BLU"场"HIB"】"NOR,
        ([
                "msgcolor"      : NOR HIB,
                "noemote"       : 1,
        ]),
    }),
    ({
        CHAT,
        "chat",
        PLAYER,
        CYN "【"HIC"闲"NOR CYN"聊"HIC"】"NOR,
        ([
                "msgcolor"      : NOR HIC,
        ]),
    }),
    ({
        RUMOR,
        "rumor",
        PLAYER,
        MAG "【"NOR HIM"谣"NOR MAG"言"NOR HIM"】"NOR,
        ([
                "wizlevel"      : 1,
                "msgcolor"      : NOR HIM,
        ])
    }),
    ({
        MESS,
        "mess",
        PLAYER,
        HIK "【"HIW"江"NOR HIK"湖"HIW"】"NOR,
        ([
                "time"          : 1,
                "msgcolor"      : NOR HIW,
                "samecolor"     : 1,
                "notalk"        : 1,
        ])
    }),
    ({
        WIZ,
        "wiz",
        IMMORTAL,
        YEL "【"HIY"巫师"NOR YEL"】"NOR,
        ([
                "msgcolor"      : NOR HIG,
                "nameraw"       : 1,
        ]),
    }),
    ({
        SYS,
        "sys",
        WIZARD,
        RED "【"HIR"系"NOR RED"统"HIR"】"NOR,
        ([
                "time"          : 1,    // 显示时间
                "msgcolor"      : NOR RED,
        ]),
    }),
    ({
        NCH,
        "nch",
        WIZARD,
        BLU "【"HIB"监"NOR BLU"测"HIB"】"NOR,
        ([
                "time"          : 1,
                "msgcolor"      : NOR HIB,
                //"listener"    : ({ get_object(INTERMUD2_D) });
        ]),
    }),
    ({
        DEBUG,
        "debug",
        WIZARD,
        WHT "【"HIW"调"NOR WHT"试"HIW"】"NOR,
        ([
                "time"          : 1,
                "msgcolor"      : NOR HIW,
        ]),
    }),
    ({
        NEWS,
        "news",
        PLAYER,
        GRN "【"HIG"新"NOR GRN"闻"HIG"】"NOR,
        ([
                "time"          : 1,
                "nameraw"       : 1,
                "msgcolor"      : NOR YEL,
                "notalk"        : 1,
        ]),
    }),
    ({
        //GWIZ 被别的地方定义过
        256,
        "gwiz",
        WIZARD,
        GRN "【"HIG"网际%T"NOR GRN"】"NOR,
        ([
                "nameraw"       : 1,
                "msgcolor"      : NOR HIG,
                "intermud"      : INTERMUD2_D,
                "channel"       : "CREATOR",
                "subchannel"    : 1,
                "newtitle"      : (: stringp($1) ? "-"+$1 : "" :),
        ]),
    }),
    ({
        OTHER,
        "other",
        PLAYER,
        CYN "【"HIC"未"NOR CYN"知"CYN"%T"HIC"】"NOR,
        ([
                "msgcolor"      : NOR CYN,
                "intermud"      : INTERMUD2_D,
                "channel"       : "",
                "subchannel"    : 1,
                "newtitle"      : (: stringp($1) ? ("-"+HIG+$1+NOR) : "" :),
        ]),
    }),
    ({
        AD,
        "ad",
        PLAYER,
        HIK "【"WHT"广"NOR HIK"告"WHT"】"NOR,
        ([
                "nameraw"       : 1,
                "noemote"       : 1,
                "msgcolor"      : NOR HIK,
        ]),
    }),
    ({
        FAMILY,
        "family",
        PLAYER,
        HIW"【"NOR"%T"NOR HIW"】"NOR,
        ([
                "msgcolor"      : NOR HIG,
                "subchannel"    : 1,
                "filter"        : (: $1->query_family() == (stringp($2) ? $2 : $2->query_family()) || wiz_level($1) > 1 :),
                "newtitle"      : (: (stringp($1) ? $1 : $1->query_family()) || "无门派":),
        ]),
    }),
    ({
        PARTY,
        "party",
        PLAYER,
        HIW"【"NOR"%T"NOR HIW"】"NOR,
        ([
                "msgcolor"      : NOR HIG,
                "subchannel"    : 1,
                "filter"        : (: $1->query_bunch() == (stringp($2) ? $2 : $2->query_bunch()) || wiz_level($1) > 1 :),
                "newtitle"      : (: (stringp($1) ? $1 : $1->query_bunch()) || "无帮派":),
        ]),
    }),
    ({
        STOCK,
        "stock",
        PLAYER,
        YEL "【"NOR HIY"股"NOR YEL"市" NOR HIY"】"NOR,
        ([
                "time"          : 1,
                "nameraw"       : 1,
                "notalk"        : 1,
                "msgcolor"      : NOR HIR,
        ]),
    }),
    ({
        AUC,
        "auc",
        PLAYER,
        BLU "【" HIB "拍"NOR BLU"卖" HIB "】"NOR,
        ([
                "time"          : 1,
                "notalk"        : 1,
                "msgcolor"      : NOR HIB,
        ]),
    }),
    ({
        COMBAT,
        "combat",
        PLAYER,
        RED "【"NOR HIR"战" NOR RED"斗" HIR"】"NOR,
        ([
                "time"          : 1,
                "notalk"        : 1,
                "msgcolor"      : NOR HIR,
        ]),
    }),
    ({
        GROUP,
        "gt",
        PLAYER,
        HIW"【"NOR WHT"%T"HIW"】"NOR,
        ([
                "msgcolor"      : NOR HIW,
                "subchannel":   1,
                "filter"        : (: query_temp("battle/team_name", $1) == (stringp($2) ? $2 : query_temp("battle/team_name", $2)) || wiz_level($1) > 1 :),
                "newtitle"      : (: (stringp($1) ? $1 : query_temp("battle/team_name", $1)) || "无队伍":),
        ]),
    }),
     ({
        DT,
   "dt",
        PLAYER,
   WHT "【"NOR HIW"洞"NOR WHT"天" NOR HIW"】"NOR,
        ([
                "msgcolor"      : NOR HIW,
                "time"  :       1,
           //"notalk"        :       0,
        ]),
    }),
});

nosave mapping replace_word = ([
        "干你娘":       "******",
        "妈逼":         "******",
        "妈的逼":       "******",
        "妈个逼":       "******",
        "妈的个逼":     "******",
        "逼养的":       "******",
        "傻逼":         "******",
]);

int valid_channel(int level, string channel)
{
        foreach(string *data in info)
        {
                if( data[1] == channel && level >= atoi(data[2]) )
                        return 1;
        }

        return 0;
}

varargs int do_channel(object me, string channel, string msg, mixed raw)
{
        int t,emote,internal_flag,name_raw;
        object *fit_users;
        class channel_class ch;
        string channel_title, idname, send_msg, time, my_id, my_idname, color, subchannel;
        string lfn;
        mixed lt;

        if( !channel || channel == "" || !me ) return 0;

        if( query("chblk_on", me) )
                return notify_fail("你的聊天频道给关闭了！唯一的办法就是请求在线玩家投票开通。\n");

        if( query("chblk_tt", me) > time() ) {
                                me->start_busy(10);
                        return notify_fail("你的聊天频道给关闭了！等" + chinese_number(abs(query("chblk_tt", me) - time()) / 60 + 1) + "分钟后自动开通。\n");
        }

        if( me->is_chatter() )
                return notify_fail("聊天魂魄目前不能使用各种频道。\n");

        if( playerp(me) && me->ban_say(1) ) return 0;

        // 检查是否为表情指令
        if( channel[<1] == '*' ) { emote = 1; channel = channel[0..<2]; }

        if( sscanf(channel, "gwiz-%s", subchannel) ) channel = "gwiz";
        if( sscanf(channel, "other-%s", subchannel) ) channel = "other";

        if( !classp(ch = channels[channel]) ) return 0;

        // player broadcasting need consume jing
        if( playerp(me) && !wizardp(me) && channel == "rumor" &&
            !objectp(present("rumor generator", me)) )
                if( query("jing", me)>50 )
                        addn("jing",-random(36), me);
                else
                        return notify_fail("你已经没力气散播谣言了！\n");

        if( query("doing", me) == "scheme"){
                if( query("jing", me)<100 )
                        return notify_fail("你现在的精神不济，等一会儿吧。\n");
                addn("jing", -50, me);
        }

        if( channel == "family" && interactive(me) && !wizardp(me) && !query("family", me) )
                return notify_fail(pnoun(2, me)+"并未加入任何门派。\n");

        if( channel == "party" && interactive(me) && !wizardp(me) && !query("bunch", me) )
                return notify_fail(pnoun(2, me)+"并未加入任何帮派。\n");

        my_id = me->query_id(1); // 不带颜色
        name_raw = ch->extra["nameraw"];
        my_idname = me->query_idname(name_raw); // 是否假装了别人

        // 若有子频道标记, 则分析子频道名称
        if( ch->extra["subchannel"] )
                if( msg && sscanf(msg, "[%s] %s", subchannel, msg) ) internal_flag=1;
        // 检查本频道之特殊替换频道名
        if( ch->extra["newtitle"] )
        {
                //channel_title = replace_string(ch->msg, "%T", evaluate(ch->extra["newtitle"], stringp(raw) ? raw : (wizardp(me)||previous_object(1)==find_object(INTERMUD2_D)) ? subchannel || me : me));
                channel_title = replace_string(ch->msg, "%T", evaluate(ch->extra["newtitle"], stringp(raw) ? raw : subchannel || me));
        }
        else
                channel_title = ch->msg;

        // 假如是使用者, 则检查频道注册
        if( interactive(me) && !(ch->number & users[me]) )
        {
                if( wiz_level(my_id) < ch->level ) return 0;

                users[me] |= ch->number;
                set("channels", query("channels",me) | ch->number, me);
                tell(me, "开启 "+channel_title+" 频道。\n");

                if( !msg ) return 1;
        }

        // 若没有输入讯息
        msg = msg || (emote ? "看起来表情丰富。" : "..." );

        // 检查ID, NAME
        idname = my_idname || query("channel_id", me) || "NO_IDNAME";
        if( channel == "rumor" && idname == "NO_IDNAME" ) idname = "";

        // 整理出正在使用本频道的频道使用者
        fit_users = keys(filter(users, (: $(ch->number) & $2 :)));
        fit_users -= ({ 0 });

        // 检查本频道的使用之过滤条件
        if( ch->extra["filter"] )
        {
                if( sizeof(fit_users) )
                        fit_users = filter(fit_users, ch->extra["filter"], stringp(raw) ? raw : (wiz_level(me) > 1 ? subchannel || me : me));
        }


        // 若此频道有显示时间标记

        if( ch->extra["time"] == 1 )
                time = HIW+ctime(time())[11..15]+NOR" ";
        else if( ch->extra["time"] == 2 )
                time = HIW+ctime(TIME_D->query_game_time())[11..15]+NOR" ";
        else
                time = "";

        if( ch->extra["samecolor"] )
        {
                idname = remove_ansi(idname);
        }
        // 若使用表情模式
        if( emote )
        {
                string verb, arg;
                if( ch->extra["noemote"] )
                        return notify_fail("这个频道不支持表情动词。\n");
                verb = msg;
                sscanf(msg, "%s %s", verb, arg);

                if( EMOTE_D->is_emote(verb) )
                        msg = EMOTE_D->do_emote(me, verb, arg, 1) || (idname + msg);
                else
                        msg = idname + msg;
        }

        // 若此频道有设定特定讯息颜色
        if( ch->extra["msgcolor"] )
        {
                color = ch->extra["msgcolor"];
                /*
                if( ch->extra["samecolor"] )
                {
                        msg = remove_ansi(msg);
                        idname = remove_ansi(idname);
                }
                */
        }
        else
                color = "";

        // 限制洗荧幕的行为
        //if( undefinedp(raw) && previous_object() != this_object() && me->is_character() )
        if( undefinedp(raw) && previous_object() != this_object() && userp(me) )
        {
                int nowtime = time();

                if( nowtime - query_temp("lastchat/time", me) < 1 )
                {
                        if( addn_temp("lastchat/warning", 1, me) > 100 )
                        {
                                tell(me, "由于"+pnoun(2, me)+"大量重覆尝试不合法的频道发言动作，从现在起将自动封锁"+pnoun(2, me)+"的指令功能。\n");
                                set_temp("command_delay", time()+30, me);
                                CHANNEL_D->channel_broadcast("sys", me->query_idname()+"大量重覆尝试不合法的频道发言动作，从现在起将自动限制指令速度。\n");
                        }
                        return notify_fail("公开频道不能连续发送讯息。\n");
                }
                if( query_temp("lastchat/msg", me) == msg && nowtime - query_temp("lastchat/time", me) < 300 )
                {
                        if( addn_temp("lastchat/repeattimes", 1, me) > 5 )
                        {
                                if( addn_temp("lastchat/warning", 1, me) > 100 )
                                {
                                        tell(me, "由于"+pnoun(2, me)+"大量重覆尝试不合法的频道发言动作，从现在起将自动封锁"+pnoun(2, me)+"的指令功能。\n");
                                        set_temp("command_delay", time()+30, me);
                                        CHANNEL_D->channel_broadcast("sys", me->query_idname()+"大量重覆尝试不合法的频道发言动作，从现在起将自动限制指令速度。\n");
                                }
                                return notify_fail("公开频道不能连续发送相同讯息。\n");
                        }
                }
                else
                {
                        set_temp("lastchat/msg", msg, me);
                        delete_temp("lastchat/repeattimes", me);
                }

                set_temp("lastchat/time", nowtime, me);
        }
        // 玩家无法用 News 频道发言
        if( ch->extra["notalk"] )
        {
                if( !wizardp(me) && interactive(me) )
                {
                        return notify_fail("玩家无法使用这个频道发言。\n");
                }
        }
        // 若是网际频道
        if( ch->extra["intermud"] && interactive(me) )
        {
                string intermud_msg = msg;
                if( emote ) intermud_msg = replace_string(msg, my_idname, my_idname[0..<2] + "@NT)");

                if( channel == "gwiz" )
                        ch->extra["intermud"]->send_gwiz_msg(subchannel, capitalize(me->query_id(1)), me->query_name(), intermud_msg, emote);
                else
                if((!internal_flag && subchannel!="") || ( internal_flag && member_array(subchannel,keys(channels))==-1 ))
                        ch->extra["intermud"]->send_gchannel_msg(subchannel, capitalize(me->query_id(1)), me->query_name(), intermud_msg, emote);
                else         subchannel="站内";
        }

        // 若有纯讯息参数或表情参数, send_msg = 频道名称 + 讯息
        if( !undefinedp(raw) || emote )
                send_msg = channel_title+time+color;
        else
                send_msg = channel_title+time+color+idname+"："+color;


        // 处理精简字串
        send_msg = send_msg + msg + NOR + (noansi_strlen(msg) > 0 && remove_ansi(msg)[<1] == '\n' ? "" : "\n");


        // replace string
        foreach(string a , string b in replace_word)
        send_msg=replace_string(send_msg,a,b);

        // replace ansi for %^RED%^
        //send_msg = replace_usa_ansi(send_msg);

        fit_users -= ({ 0 });
        // 使用者权限处理, 等级高等于说话者直接显示名称
        if( ch->extra["wizlevel"] && me->is_character() )
        {
                int my_level = wiz_level(my_id);
                string level_send_msg;
                object *level_fit_users;

                level_fit_users = filter(fit_users, (: wizardp($1) && $(my_level) <= wiz_level($1) :));
                if( random(50) || wizardp(me) || !userp(me) )
                        switch(query("env/rumor", me))
                {
                case 1:
                        {
                                string random_idname;
                                object* fit_users_without_wiz = filter_array(fit_users, (: !wizardp($1) :));

                                if( !sizeof(fit_users_without_wiz) )
                                        random_idname = fit_users[random(sizeof(fit_users))]->query_idname();
                                else
                                        random_idname = fit_users_without_wiz[random(sizeof(fit_users_without_wiz))]->query_idname();

                                level_send_msg = replace_string(send_msg, my_idname, "["+my_idname+"]-假冒的" + random_idname );
                                send_msg = replace_string(send_msg, my_idname, "假冒的" + random_idname );
                                break;
                        }
                case 2:
                        {
                                if( undefinedp(query_temp("rumor_serial",me)) )
                                {
                                        water_number += 1 + random(50);
                                        set_temp("rumor_serial", water_number,me);
                                }
                                level_send_msg = replace_string(send_msg, my_idname, "["+my_idname+"]-"+(query("gender", me) == "男性"?"Mr.":"Miss")+  query_temp("rumor_serial",me) );
                                send_msg = replace_string(send_msg, my_idname, (query("gender", me) == "男性"?"Mr.":"Miss")+  query_temp("rumor_serial",me));

                                break;
                        }
                default:
                        level_send_msg = replace_string(send_msg, my_idname, "["+my_idname+"]-某人(Someone.)");
                        send_msg = replace_string(send_msg, my_idname, "某人(Someone.)");
                        break;
                }
                else
                {

                        level_send_msg = replace_string(send_msg, my_idname, "["+my_idname+"]-穿帮的"+my_idname);
                        send_msg = replace_string(send_msg, my_idname, "穿帮的"+my_idname);
                }

                fit_users -= level_fit_users;

                // 权限足够之使用者
                //tell(level_fit_users, level_send_msg, CHNMSG);
                tell(level_fit_users, level_send_msg, "channel:"+channel); // 支持tomud

                level_fit_users->add_msg_log(channel, level_send_msg);
                SPECIAL_NPC->receive_report(me, channel);
        }

        //tell(fit_users, send_msg, CHNMSG);
        tell(fit_users, send_msg, "channel:"+channel); // 支持tomud

        if( userp(me) && channel == "chat" && random(100) < 20 )
        {
                addn("active", 1, me);
                tell_object(me, HIY "\n由于您的踊跃发言让王者归来更加热络，特别为您增加活跃值一点。\n" NOR);


        if ( query("krok/award", me) == krok_award ) {
                int krok_count;
                addn("krok/count", 1, me);
                krok_count = query("krok/count", me);
                if (krok_count > krok_top1) {
                        krok_id1 = query("id", me);
                        krok_top1 = krok_count;
                        if (krok_id2 == query("id", me)) krok_id2 = "";
                } else if ((krok_count > krok_top2) && (krok_id1 != query("id", me))) {
                        krok_id2 = query("id", me);
                        krok_top2 = krok_count;
                }
        } else {
                set("krok/award", krok_award, me);
                set("krok/count", 0, me);
        }

        if ( (time() - krok_award) > 14400)
        {
                object krokob1, krokob2, item;
                krokob1 = find_player(krok_id1);
                if (krokob1 && userp(krokob1)) {
                        tell_object(krokob1, HIY "\a你在聊天大会上勇夺" HBRED HIY "麦霸" NOR HIY "荣誉，获奖钢镚和二册万象书。\n" NOR);
                        item = new("/u/redl/npc/obj/penny");
                        item->move(krokob1, 1);
                        item = new("/d/dongtian/obj/wanxiangbook");
                        item->move(krokob1, 1);
                        item = new("/d/dongtian/obj/wanxiangbook");
                        item->move(krokob1, 1);
                }
                krokob2 = find_player(krok_id2);
                if (krokob2 && userp(krokob2)) {
                        tell_object(krokob2, HIY "\a你在聊天大会上勇夺" HBRED HIY "话痨" NOR HIY "荣誉，获奖钢镚和十张金票。\n" NOR);
                        item = new("/u/redl/npc/obj/penny");
                        item->move(krokob2, 1);
                        item = new("/clone/money/thousand-gold");
                        item->set_amount(10);
                        item->move(krokob2, 1);
                }
                krok_award = time();
                krok_top1 = krok_top2 = 0;
                krok_id1 = krok_id2 = "";
        }




        }

        fit_users->add_msg_log(channel, send_msg);

        if( arrayp(ch->extra["listener"]) )
        {
                ch->extra["listener"] -= ({ 0 });
                if( sizeof(ch->extra["listener"]) )
                        ch->extra["listener"]->relay_channel(me, channel, msg);
        }

        switch(channel)
        {
        case "msg":
                break;
        case "chat":
        case "family":
        case "party":
        case "rumor":
        case "war":
        case "gwiz":
        case "sos":
        case "wiz":
                if( !stringp(msg_log) ) msg_log = "";

                t = time();
                msg_log += sprintf(" %s\n%s",
                                log_time(),filter_color(send_msg));
                if( strlen(msg_log) > 8000 || t - log_from > 900 ) {
                        lt = localtime(t);

                        lfn = sprintf("channel/%d-%d-%d", lt[LT_YEAR],
                              lt[LT_MON] + 1, lt[LT_MDAY]);
                        assure_file(LOG_DIR + lfn);
                        log_file(lfn, msg_log);
                        msg_log = "";
                        log_from = t;
                }
                break;
        default:
                break;
        }
        return 1;
}

void register_relay_channel(string channel)
{
        class channel_class ch;
        object ob;
        ob = previous_object();
        ch = new(class channel_class);

        if( undefinedp(channels[channel]) || !ob )
                return;
        if( !classp(ch = channels[channel]) )
                return;

        if( arrayp(ch->extra["listener"]) ) {
                if( member_array(ob, ch->extra["listener"]) >= 0 )
                        return;
                ch->extra["listener"] += ({ ob });
        }
        else    ch->extra["listener"] = ({ ob });
}

/* 注册频道 */
nomask void register_channel(object me, int channel)
{
        if( !channel ) return;
        if( undefinedp(users[me]) ) users[me] = channel;
        else users[me] |= channel;
}

/* 移除注册 */
nomask void remove_register(object me, int channel)
{
        if( !channel ) return;
        users[me] ^= channel;
        if( users[me] == 0 ) map_delete(users, me);
}

/* 直接移除一位使用者 */
nomask void remove_user(object me)
{
        map_delete(users, me);
}

/* 所有玩家重新注册频道 */
nomask void reset_all_register()
{
        users = allocate_mapping(0);
        filter_array( users(), (: register_channel($1, query("channels",$1)) :) );
}

nomask varargs string *query_channel_users(string channel, int flag)
{
        class channel_class ch;
        string *res = allocate(0);

        if( undefinedp(ch = channels[channel]) ) return res;
        foreach(object ob, int i in users)
        {
                if( !flag && (i & ch->number) ) res += ({ ob });
                if( flag && !(i & ch->number) ) res += ({ ob });
        }
        return res;
}

nomask int query_default_channel(string id)
{
        int default_channel=0, level = wiz_level(id);
        foreach( string name, class channel_class ch in channels )
        {
                if( level < ch->level ) continue;
                default_channel |= ch->number;
        }
        return default_channel &~ DEFAULT_REFUSE;
}

nomask varargs mixed query_using_channel(object user, int flag)
{
        int channel = users[user];
        string using_channel = "";
        string *using_ch = ({});

        if( channel )
                foreach( string name, class channel_class ch in channels )
                if( channel & ch->number )
                {
                        if( flag ) using_ch += ({ name });
                        else using_channel += " "+name;
                }

        if( flag ) return using_ch;
        return using_channel == "" ? "无" : using_channel;
}

varargs void channel_broadcast(string channel, string msg, mixed arg)
{
        switch(channel)
        {
        case "family":
                msg = NOR GRN"门派"+HIG+"新闻 "NOR+msg; break;
        case "party":
                msg = NOR CYN"帮派"+HIC+"新闻 "NOR+msg; break;
        default: break;
        }

        if( undefinedp(arg) )
                do_channel(this_object(), channel, msg, 1);
        else if( objectp(arg) )
                do_channel(arg, channel, msg, 1);
        else
                do_channel(this_object(),channel, msg, arg);

}

varargs void announce(object me, string msg)
{
        shout("\n\a"HIR + (objectp(me) ? me->query_idname() + HIR"发布":"") + "系统公告 ("HIW + ctime(time()) + NOR + HIR")：\n\n"NOR + msg + NOR"\n\n");
}


void create()
{
        class channel_class ch;

        if( clonep() ) destruct(this_object());

        seteuid(getuid());
        set("channel_id", "频道精灵");

        channels = allocate_mapping(0);
        users = allocate_mapping(0);
        water_number = 10000;
        foreach( mixed *c in info )
        {
                ch = new(class channel_class);
                ch->number     = atoi(c[0]);
                ch->level      = atoi(c[2]);
                ch->msg        = c[3];
                ch->extra      = c[4];
                channels[c[1]] = ch;
        }
        reset_all_register();

}


string query_name()
{
        return "频道系统(CHANNEL_D)";
}
