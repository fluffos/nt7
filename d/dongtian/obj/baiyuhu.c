// This program is a part of NITAN MudLIB 
// redl 2013/11
#include <ansi.h>

inherit ITEM;
inherit F_CLEAN_UP;

void create()
{
        set_name(NOR HIW "白玉" HIC "笏" NOR, ({"baiyu hu", "hu"}));
        set_weight(50);
                set("unit", "块");
                set("value", 1);
                set("weight", 5);
                set("material", "jade");
                set("long", "这是块光洁无暇的法器，记载洞天中水晶头颅所授的玄奥意恉。\n");
                set("set_data", 1); 
                set("auto_load", 1); 
                set("no_sell", 1);
                set("no_pawn", 1);        
                setup();
}   

int is_learned(object me) 
{
        mapping cg_data;
        
        //DEBUG_CHANNEL("is_learned");
        cg_data = query("dongtian/cg_data", me);
        if (undefinedp(cg_data) || !mapp(cg_data) || !sizeof(cg_data)) {
                return 0;
        }       
        return cg_data["guid"];
}

int fangqiall(object me) 
{
        mapping cg_data, mysks;
        object gcroom;
        
        //DEBUG_CHANNEL("fangqiall");
        cg_data = query("dongtian/cg_data", me);
        mysks = cg_data["skills_id"];
        if (query_temp("flag_use_baiyuhu", me)) 
                message_vision(NOR + "$N" + NOR + "把$n" + NOR + "紧紧贴在额头上。\n", me, this_object());
        else
                message_vision(append_color(NOR + YEL + "虚空中穿过来一只大如山岳的巨掌，死死按住$N" + NOR + YEL + "动弹不得。\n" + NOR, YEL), me);
        foreach(string skid in keys(mysks)) {//to_chinese(skid) 老显示仙器 ?
                if (query_temp("flag_use_baiyuhu", me)) {
                        message_vision(NOR + "无数金色蝌蚪文涌向$n" + NOR + 
                                "，$N" + NOR + 
                                "关于『" + NOR + CYN + (string)skid + NOR + "』的记忆被抹去了。\n" + NOR, me, this_object());
                } else {
                        message_vision(NOR + "无数金色蝌蚪文涌向巨掌的手心" + NOR + 
                                "，$N" + NOR + 
                                "关于『" + NOR + CYN + (string)skid + NOR + "』的记忆被抹去了。\n" + NOR, me);
                }
                me->delete_skill(skid); 
                delete("can_perform/" + skid, me);
                tell_object(me, NOR + "你忘记了关于『" + NOR + CYN + (string)skid + NOR + "』的所有内容(包括绝招)。\n" + NOR);
        }
        gcroom = get_object(cg_data["center"]);
        gcroom->cg_remove(me);
        delete("dongtian/cg_data", me);
        me->save();
        if (query_temp("flag_use_baiyuhu", me)) {
                delete_temp("flag_use_baiyuhu", me);
                log_file("static/dongtiancg", ctime(time()) + " 放弃 " + query("id", me) + " \n");
                destruct(this_object());
        } else {
                log_file("static/dongtiancg", ctime(time()) + " 抹去 " + query("id", me) + " \n");
        }
        return 1;
}

int do_use(string arg)
{
        object me = this_player();
        
        
        if (!arg || arg!=query("id")) {
                return 0;
        }
        
        if (!is_learned(me)) {
                tell_object(me, NOR "你并没有在任何洞天的传功楼学过东西。\n" NOR);
                return 1;
        }
        set_temp("flag_use_baiyuhu",1 , me);
        fangqiall(me);
        return 1;
}

void init()
{
        object me = this_player();
        if (!playerp(me)) return;
        add_action("do_use", "use");
}



