// This program is a part of NITAN MudLIB 
// redl 2013/5 
// 私有，小心被利用刷屏和干扰机器人

#include <ansi.h>
inherit ITEM;


int start_make(object me);
void save_music(string str);

int timeintervals = 3, idx = 0, imax;
string *text = ({});
string qz = "  ∽ ";

void create()
{
        set_name(WHT "音乐盒" NOR, ({"music box", "box"}));
        set_weight(1);
                set("longx", WHT"这是块拇指大小的檀木，上面横托着个白银的核桃，核桃的根\n"
                                           "部伸出来一个小巧的果柄，檀木底部刻着“paroles et musique”。\n"
                                        HIK"(指令：mplay、 mmake、 mdelay)\n"NOR);
                set("unit", "个");
                set("material", "silver");
                set("value", 2000000000);
                set("nj", 20); 
                set("set_data", 1); 
                set("auto_load", 1); 
}

string long()
{
        string *t = query("content");
        int i = sizeof(t);
        if (i < 1) return query("longx") + qz + "空白……\n" + NOR; 
                else return query("longx") + qz + t[0] + "\n" + NOR; 
}

int init()
{
        add_action("do_make", "mmake");
        add_action("do_delay", "mdelay");   
        add_action("do_play", "mplay");   
}

int do_delay(string arg)
{
        if (!arg && arg!="+" && arg!="-") return notify_fail("格式：mdelay + 或者 mdelay -\n"); 
        if (query("timeintervals")) timeintervals = query("timeintervals");
        if (arg=="+") {
                if (timeintervals<9) {
                        timeintervals += 1;
                set("timeintervals", timeintervals);
                }
                return notify_fail("当前播放间隔："+chinese_number(timeintervals)+"秒\n"); 
        }
                if (timeintervals>1) {
                        timeintervals -= 1;
                set("timeintervals", timeintervals);
                }
                return notify_fail("当前播放间隔："+chinese_number(timeintervals)+"秒\n"); 
}


int do_make(string arg)
{
        object me, ob;
        me = this_player();
        ob = this_object();
        //if( !arg && arg!="music box" && arg!="box") return 0;

    message_vision(YEL"$N拿出一个银白色的" + query("name") + YEL "..\n"NOR,me);
    start_make(me);
    return 1;
}


int start_make(object me)
{
        //write("为我写一首歌吗？:\n");
        me->edit( (: save_music :) );
        return 1;
}

void save_music(string str)
{
        if (strlen(str)>8192) {
                write(NOR "太臭太长了。\n");
                return;
        }
        message_vision(YEL"$N在" + query("name") + YEL "里录入了一首歌。\n"NOR, this_player());
                text = explode( str, sprintf("%c", 10) );
        set("content", text);
}

int do_play(string arg)
{
        object me, ob;
        me = this_player();
        ob = this_object();
        //if( !arg && arg!="music box" && arg!="box") return 0;
        if (query_temp("starting")) return notify_fail("这个盒子已经在播放音乐了。\n"); 
        if (query("nj") < 1) return notify_fail("这个盒子已经坏了。\n"); 
        
        addn("nj", -1);
        addn("value", -100000000);
        
        text = query("content");
        imax = sizeof(text);
        if (imax < 1) return notify_fail("请先用 mmake 录入\n"); 
        
    message_vision(YEL"$N拿出一个"WHT"核桃"YEL"轻轻地摇动果柄，\n"
                                "一阵悦耳动听的歌声缓缓的流进你的耳朵...\n"NOR,me);
    idx = 0;
    if (query("timeintervals")) timeintervals = query("timeintervals");
    set_temp("starting", 1);
    set("no_give", "请让音乐播放完成...");
    set("no_store", "请让音乐播放完成...");
    set("no_drop", "请让音乐播放完成...");
    set("no_sell", "请让音乐播放完成...");
    set("no_steal", "请让音乐播放完成...");
    set("no_beg", "请让音乐播放完成...");
    //message_vision(NOR, me);
    call_out("start_play", timeintervals, me);
    return 1;
}

int start_play(object me)
{
        if (idx < imax) {
                message_vision(NOR + HIK + qz + NOR + text[idx] + "\n" + NOR, me);
                call_out("start_play", timeintervals, me);
        }
                else {
                        //message_vision(NOR + HIK + qz + NOR + "(ending...)\n" + NOR, me);
                    delete("no_give");
                delete("no_store");
                delete("no_drop");
                delete("no_sell");
                delete("no_steal");
                delete("no_beg");
                        delete_temp("starting");
                    message_vision(YEL"$N停止了摇动果柄，一种空落的感觉涌上心头。\n"NOR,me);
                    tell_object(me, NOR "剩余播放次数：" + chinese_number(query("nj")) + "次。\n" NOR);
                }
        idx += 1;
        return 1;
}



