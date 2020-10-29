#include <ansi.h> 
inherit NPC;

object *players = ({});

void set_players(object *ob) {
        players = ob;
}

void add_player(object ob) {
        if(member_array(ob,players)==-1) {
                players += ({ob});
                message_vision(BLU"$N对$n说道：谢谢！\n"NOR,this_object(),ob);
        } else
                message_vision(BLU"$N对$n说道：你已经答应帮忙，你不会反悔吧！\n"NOR,this_object(),ob);
}

object* query_players() {
        players -= ({0});
        return players;
}

void play_sound_0(object speaker,int index);

void create()
{
        set_name("太监", ({ "tai jian","tai", "jian" }) );
        set("gender", "无性" );
        set("age", 40);
        set("str", 50);
        set("con", 30);
        set("dex", 22); 
        set("int", 50);
 
        set("long","他是皇宫内的皇帝身旁非常得宠一个太监。");
        set("max_qi", 8000000);
        set("eff_qi", 480000);        
        set("max_jing", 8500000);
        set("eff_jing",850000);
        set("neili", 8000000);
        set("max_neili", 4500000);
        set("max_jingli", 500000);
        set("combat_exp", 300000000);

        set_skill("force", 2000);
        set_skill("parry", 2000);
        set_skill("dodge", 2000);
        set_skill("sword", 2000);
        set_skill("unarmed", 2000);
        set_skill("pixie-jian", 2000);        
        set_skill("literate", 2000);
        set_skill("martial-cognize", 2000);
        set_skill("kuihua-mogong", 2000);

        map_skill("force", "kuihua-mogong");
        map_skill("dodge", "kuihua-mogong");
        map_skill("unarmed", "kuihua-mogong");
        map_skill("sword", "kuihua-mogong");
        map_skill("parry", "kuihua-mogong");

        prepare_skill("unarmed", "kuihua-mogong");

        set_temp("apply/attack", 3000);
        set_temp("apply/defense", 3000);
        set_temp("apply/damage", 1500);
        set_temp("apply/unarmed_damage", 1500);
        set("no_corpse", 1);
        setup();
        
        carry_object("/d/fuzhou/obj/xiuhua")->wield();
        carry_object("/d/wanjiegu/npc/obj/qi-dress")->wear();
}  

void init()
{       
        object ob; 
        ::init();
        
        if( interactive(ob = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, ob);
        }
        add_action("do_answer", "answer");
        add_action("do_accept", "accept");
        add_action("do_help", "help");
} 

void greeting(object ob)
{
        if( !ob || environment(ob) != environment() ) return;
        if( query_temp("开场白结束") || query_temp("开始说开场白") || query_temp("任务") )
                return;
                
        message_vision(CYN "$N有气无力地说道：这位" + RANK_D->query_respect(ob) +
                "，你是来为皇宫清除叛逆的吗？？(answer yes/no)\n" NOR, this_object(), ob);
} 

int do_answer(string arg) {
        if(arg=="yes") {
                if(query_temp("in_speech"))
                        return 0;
                if(present("tape",environment()))
                        return 0;
                set_temp("开始说开场白",1);
                set_temp("in_speech", 1);
                play_sound_0(this_object(),0);
        } else if(arg=="no") {
                message_vision(BLU"$N说道：谁想听你这个太监废话！\n",this_player());
        } else
                return notify_fail("你要回答什么？\n");
        return 1;
}

void play_sound_0(object speaker,int index) {
        if(!environment())
                return;
        if(!speaker)
                return;        
        switch (index)  {
                case(0):
                        tell_room(environment(),CYN"太监说道：天牢总管太监总管李莲英在天牢中锻炼出一批死士来刺杀圣上......\n"NOR);
                        break;
                case(1):
                        tell_room(environment(),CYN"太监说道：由于天牢死士个个都属于武林人氏，武功高强，所以圣上寻求各位勇士前来帮助。\n"NOR);
                        break;
                case(2):
                        tell_room(environment(),CYN"太监说道：你愿意为宫廷清理叛逆，铲除李莲英吗？(accept yes/no)\n"NOR);
                        set_temp("开场白结束", 1, speaker);
                        break;
                default: 
                        delete_temp("in_speech", speaker);
                        return;

        }
        call_out("play_sound_0",1,speaker,++index);
}

int do_accept(string arg) {
        object ob,*team;
        object me = this_player();
        if(!query_temp("开场白结束"))
                return 0;
        if(query_temp("任务"))
                return 0;
        if(arg=="yes") {                
                delete_temp("开场白结束");
                team = me->query_team();
                if(!team || sizeof(team)==0)
                        team = ({ me });
                set_players(team);
                set_temp("任务", 1);
                ob = new("/maze/prison/npc/obj/key");
                ob->move(me, 1);
                tell_room(environment(),CYN"太监说道：这是进入天牢的钥匙，现在交给你，希望" + RANK_D->query_respect(me) + 
                        "能完成圣上发布下来的任务。\n" NOR);
                message_vision(HIY "$N" HIY "说罢" HIY "便领着$n" HIY "快步朝地上牢房走去。\n\n" NOR, this_object(), me);

                ob = load_object("/f/prison/"+query("id", me) +"/tianlao");
                me->move(ob);
                tell_object(me, CYN + name() + "说道：就是这里，接下来就看您了。\n"
                        HIC + name() + "说完便急急忙忙赶了回去。\n" NOR);                
        }        
        else if(arg=="no") {
                delete_temp("开场白结束");
                delete_temp("开始说开场白");
                message_vision(BLU"$N说道：没好处的事情我可不干！\n",this_player());
        }
        else
                return 0;
        return 1;
}

int do_help(string arg) {
        if(arg!="tai" && arg!="tai jian")
                return 0;
        add_player(this_player());
        return 1;
}
