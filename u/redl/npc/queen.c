// This program is a part of NITAN MudLIB 
// redl 2013/4/24 

inherit NPC;
#include <ansi.h>

void create()
{
        set_name("小侍女" , ({ "shi nv", "girl", "queen" }) );
        set("title", HIY"化乐大殿"NOR);
        //set("nickname", HIM "化乐天女" NOR);
        set("gender", "女性");
        set("age", 21);
        set("long", "这是一个低调却高傲的女人，偶尔也头晕犯脾气。\n");
        set("attitude", "friendly");
        set("str", 21);
        set("con", 19);
        set("int", 36);
        set("dex", 25);
        set("per", 29);
        set("kar", 22);
        set("level",20);
        
        set("max_qi", 100000);
        set("eff_qi", 100000);
        set("qi", 100000);
        set("max_jing", 100000);
        set("eff_jing", 100000);
        set("jing", 100000);
        set("max_neili", 1);
        set("neili", 1);
        set("max_jingli", 1);
        set("jingli", 1);
        
        set("combat_exp", 200000000);

                set("inquiry", ([
               // "玉清散"   : (: ask_makesan :),
                "茶"     : "你安心坐下吧，多坐几次就有茶喝了。\n"+NOR,
                "redl"     : "那是奴婢的男主人，爱喝酒，比较二。\n"+NOR,
                "gigi"     : "那是奴婢的女主人，聪明漂亮，敏捷无双。\n"+NOR,
        ]));

        setup();
        //carry_object("/d/city/npc/cloth/moon-dress")->wear();
        carry_object("/d/city/npc/cloth/zi-dress")->wear();
        
}


void fullnow(object me)
{
    mapping my;
        delete_temp("block_msg/all", me);
        my = me->query_entire_dbase();
        my["jing"]   = my["eff_jing"]   = my["max_jing"]; 
        my["jingli"] = my["eff_jingli"] = my["max_jingli"]; 
        my["qi"]     = my["eff_qi"]     = my["max_qi"]; 
        my["neili"]  = my["max_neili"];
        my["water"]  = my["food"] = 0;
        me->clear_condition();
        me->stop_busy();
        me->clear_weak();
        me->full_self();
        me->remove_all_enemy();
}


int is_owner(object me)
{
        if ( query("id", me) != "redl" && query("couple/couple_id", me) != "redl" ) return 0;
        return 1;
}

void init() 
{ 
        object me = this_player();
        if (playerp(me)) {
                if (!query_temp("has_healredlroom", me)){
                        set_temp("has_healredlroom", 1, me);
                        message_vision(YEL "$N微微颔首浅笑，顿时$n如沐春风一般精神了。\n" NOR, this_object(), me);
                        fullnow(me);
                }
                if ( is_owner(me) ){
                        add_action("do_expel", ({"expel", "quzhu"})); 
                        add_action("do_sm", ({"sm", "da"})); 
                        add_action("do_cpat", "cpat"); 
                }
        }
} 

int do_expel(string arg)
{
        object me, ob, where, *ulist;
        
        me = this_player();
        if ( !is_owner(me) ){
                tell_object(me, NOR"你无法行使驱逐权！\n"NOR);
                return 1;
        }
        
        if (!arg || arg=="") {
                ulist  =  users();
                foreach (ob in ulist) {
                        if (is_owner(ob)) continue;
                        where = environment(ob);
                if (!where) continue;
                if (sscanf(base_name(where), "/u/redl/%*s") ||
                        sscanf(base_name(where), "/data/room/redl/%*s") ||
                        sscanf(base_name(where), "/u/gigi/%*s") ||
                        sscanf(base_name(where), "/data/room/gigi/%*s")) {
                                message_vision(YEL "$N打了个响指，屏风后涌出四个傀儡武士手持长长的斧钺枪戟，\n"
                                                                   "  把$n高高地叉在上面，齐喝一声“咄...” 用力往石阶掼了下去。\n" NOR, this_object(), ob);
                                delete_temp("can_enterredlroom", ob);
                                ob->move("/u/redl/private_room/dating");
                                message_vision(YEL "$N从石阶上骨碌骨碌滚下来，摔了个七荤八素，躺在地上无法动弹！\n" NOR, ob);
                                ob->start_busy(30);
                        }
                }
                return 1;
        }
        
        ob = find_player(arg);
        if (!ob || !objectp(ob) || !playerp(ob)) {
                tell_object(me, "你没有发现有这玩家。\n");
                return 1;
        }

        //等于summ，区别是无法获得通向大殿的资格
        message_vision(YEL "$N打了个响指，屏风后涌出四个傀儡武士手持长长的斧钺枪戟，\n"
                                        "  把$n高高地叉在上面，齐喝一声“咄...” 用力往石阶掼了下去。\n" NOR, this_object(), ob);
        delete_temp("can_enterredlroom", ob);
        ob->move("/u/redl/private_room/dating");
        message_vision(YEL "$N从石阶上骨碌骨碌滚下来，摔了个七荤八素，躺在地上无法动弹！\n" NOR, ob);
        ob->start_busy(30);
        return 1;
}

int do_sm(string arg)
{
        object me, ob;
        me = this_player();
        if ( !is_owner(me) ){
                tell_object(me, NOR"你无法行使调教权！\n"NOR);
                return 1;
        }
        if (!arg || arg=="") {
                tell_object(me, "你需要指定一位玩家。\n");
                return 1;
        }
        ob = find_player(arg);
        if (!ob || !objectp(ob) || !playerp(ob)) {
                tell_object(me, "你没有发现有这玩家。\n");
                return 1;
        }

        this_object()->command("remove all");
        message_vision(YEL "$N露出里穿的一套黑色PU镂空胸衣、黑色PU紧身短裙、黑色蕾丝吊袜带，\n"
                                           "  再迅速摸出一顶珊瑚恶魔犄角戴好，紧接着抽出黑色长皮鞭对着$n嘿嘿一笑……\n" NOR, this_object(), ob);
        for(int i = 16; i > 0; i--) {
                int rnd = random(7);
                switch(rnd)
                {
                        case 0:
                        case 1:
                                this_object()->command("whip " + query("id", ob));
                break;
                        case 2:
                        case 3:
                                this_object()->command("sm " + query("id", ob));
                break;
                        case 4:
                        case 5:
                                this_object()->command("candle " + query("id", ob));
                break;
                        case 6:
                                this_object()->command("kiss " + query("id", ob) + " 伤口");
                break;
        }
        }
        this_object()->command("wear all");
        this_object()->command("hoho " + query("id", ob));
        //ob->unconcious();
        return 1;
}

int do_cpat()
{
        message_vision(YEL "$n" NOR YEL "轻轻拍了拍$N" NOR YEL "的脑袋，$N" NOR YEL "“喵呜~”就地一滚变成了只小猫咪。\n" NOR, this_object(), this_player());
        new(__DIR__"lcat")->move(environment(this_object()));
        destruct(this_object());
        return 1;
}





