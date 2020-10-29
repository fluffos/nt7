// This program is a part of NT MudLIB
// first.c 大师兄

#include <ansi.h>

inherit NPC;
inherit F_SAVE;

string zname(object);
void reset_me(object me);// 初始化武功、经验、title 等
void create_identity (mixed master, mixed where);//为弟子重置准备(只一次)
int init_identity (object me, object master, object where);//重置弟子restore
int do_clone(object me, object ob);//完全拷贝ob的武功等给me 并保存
void self_adjust (object me); //设所有武功60 气血同reset  用于copy from master后恢复
string zm_apply();// 处理ask about 掌门事件
int do_recopy (object me); // 开始打架之前 恢复状态
void find_master (object me, object ob); // 带去掌门路上循环检测
void master_announce (object me, object who, object ob); //掌门通知
int convert_identity (object me, object ob);//更新掌门弟子
void time_out(object me, object ob);
int is_first() { return 1; }

void create()
{
        set_name("首席大弟子", ({ "zhang men", "zhangmen", "first" }) );
        set("gender", "男性" );
        set("age", 30);
        set("str", 30);
        set("int", 30);
        set("con", 30);
        set("dex", 30);
        set("per", 30);
        set("no_get", 1);
        set("no_get_from", 1);
        set("long", "这是本门首席大弟子。你如果不服，可以挑战。\n" );
        set("attitude", "heroism");
        set("combat_exp", 1000000);
        set("auto_perform", 1);
        set("current_player","none of us");
        setup();
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object me = this_object();

        create_identity(query("master_dir", me), query("start_room", me));
        set("inquiry", ([
                "首席大弟子" : (: zm_apply :),
                "掌门大师兄" : (: zm_apply :),
                "大弟子" : (: zm_apply :),
                "掌门" : (: zm_apply :),
                "挑战" : (: zm_apply :),
        ]) );
        add_action("do_reset", "reset");
}

int do_reset(string arg)
{
        object ob=this_player();
        object me=this_object();
        
        if( !wizardp(ob) ) return 0;
        
        if( arg != "zhangmen" ) return notify_fail("你要reset zhangmen吗？\n");
        set_name("掌门大弟子", ({ "zhang men", "zhangmen", "first" }) );
        me->reset_me(me);
        set("current_player", "none of us");
        save();
        write("重置"+query("family/family_name")+"掌门大师兄成功。\n");
        return 1;
}

void create_identity (mixed master, mixed where)
{
        object master_ob, where_ob;

        if( query("created") ) return;
        set("created", 1);

        if( objectp(master) ) master_ob = master;
        else    master_ob = load_object (master);

        if( objectp(where) ) where_ob = where;
        else
        {
                call_other(where,"???");
                where_ob = find_object(where);
        }
        init_identity (this_object(), master_ob, where_ob);
}

int init_identity (object me, object master, object where)
{
//      mapping skill_status;
//      string *skillnames;
//      int i;

        me->move(where, 1);
        set("where",base_name(where));

        set("gender",query("gender", master));
        set("current_master",query("id", master));
        set("current_master_base_name",base_name(master));
        set("family/generation",query("family/generation", master)+1);
        set("family/family_name",query("family/family_name", master));
        set("title",query("family/family_name", me)+zname(me));
        set("short", query("name")+"("+capitalize(query("id"))+")");

        me->restore();
        if( query("current_player", me) != "none of us" )
        {
                do_recopy(me); // copy 玩家状态
                return 1;
        }

        remove_call_out("self_adjust");
        call_out("self_adjust", 1, me);

        me->reset_me(me);
        set("current_player", "none of us", me);
        set("new_player", 1, me);
        do_clone(me, master);
        return 1;
}

// 复制数据
int do_clone(object me, object ob)
{
        object *inv, newob,weapon;
        mapping hp_status, skill_status, map_status, prepare_status;
        string *sname, *mname, *pname;
        int i/*, weapon_cnt, armor_cnt*/, temp;
        string skill1,skill2;

        seteuid( geteuid(me) );
        if( !living(me) ) me->revive();

        /* delete and copy skills */
        if( mapp(skill_status = me->query_skills()) ) {
                sname  = keys(skill_status);
                temp = sizeof(skill_status);
                for( i=0; i<temp; i++ ) {
                        me->delete_skill(sname[i]);
                }
        }
        if( mapp(skill_status = ob->query_skillc()) ) {
                sname  = keys(skill_status);
                for( i=0; i<sizeof(skill_status); i++ ) {
                        me->set_skill(sname[i], skill_status[sname[i]]);
                }
        }

        /* delete and copy skill maps */
        if( mapp(map_status = me->query_skill_map()) ) {
                mname  = keys(map_status);
                temp = sizeof(map_status);
                for( i=0; i<temp; i++ ) {
                        me->map_skill(mname[i]);
                }
        }
        if( mapp(map_status = ob->query_skill_map()) ) {
                mname  = keys(map_status);
                for( i=0; i<sizeof(map_status); i++ ) {
                        me->map_skill(mname[i], map_status[mname[i]]);
                }
        }

        /* delete and copy prepare */
        if ( mapp(prepare_status = me->query_skill_prepare()) ) {
                pname = keys(prepare_status);

                for(i=0; i<sizeof(prepare_status); i++) {
                        me->prepare_skill(pname[i]);
                }
        }
        if ( mapp(prepare_status = ob->query_skill_prepare()) ) {
                pname = keys(prepare_status);

                for(i=0; i<sizeof(prepare_status); i++) {
                        me->prepare_skill(pname[i], prepare_status[pname[i]]);
                }
        }
        
        /* unwield and remove weapon & armor */
        inv = all_inventory(me);
        for( i=0; i<sizeof(inv); i++ ) {
                destruct(inv[i]);
        }

        /* wield and wear weapon & armor */
        inv = all_inventory(ob);
        for( i=0; i<sizeof(inv); i++ ) {
                if( /*query("weapon_prop/damage", inv[i])>1000
                 || query("armor_prop/armor", inv[i])>1000
                 ||*/ query("shaolin", inv[i])
                 || inv[i]->is_unique()
                 || query("value", inv[i])>100000)continue;

                if( query("weapon_prop", inv[i]) && query("equipped", inv[i]) ) {
                        newob = new(base_name(inv[i]));
                        if( newob )
                        {
                                set("value", 0, newob);
                                set("no_get", 1, newob);
                                if( newob->move(me) ) newob->wield();
                        }
                }
                else if( query("armor_prop", inv[i]) && query("equipped", inv[i]) ) {
                        newob = new(base_name(inv[i]));
                        if( newob )
                        {
                                set("value", 0, newob);
                                set("no_get", 1, newob);
                                if( newob->move(me) ) newob->wear();
                        }
                }
        }

        /* copy entire dbase values */
        hp_status = ob->query_entire_dbase();
        set("str", hp_status["str"], me);
        set("int", hp_status["int"], me);
        set("con", hp_status["con"], me);
        set("dex", hp_status["dex"], me);
        set("age", hp_status["age"], me);
        set("max_qi", hp_status["max_qi"], me);
        set("eff_qi", hp_status["eff_qi"], me);
        set("qi", hp_status["qi"], me);
        set("max_jing", hp_status["max_jing"], me);
        set("eff_jing", hp_status["eff_jing"], me);
        set("jing", hp_status["jing"], me);
        set("max_neili", hp_status["max_neili"], me);
        set("neili", 2*hp_status["max_neili"], me);
        set("max_jingli", hp_status["max_jingli"], me);
        set("jingli", hp_status["jingli"], me);
        set("jiali", hp_status["jiali"], me);
        set("gender", hp_status["gender"], me);
        set("combat_exp", hp_status["combat_exp"], me);
        set("birthday", hp_status["birthday"], me);

        if( objectp(weapon=query_temp("weapon", me))){
                skill1=query("skill_type", weapon);
                if( objectp(weapon=query_temp("secondaly_weapon", me)) )
                        skill2=query("skill_type", weapon);
        }

        if( mapp(skill_status = me->query_skills()) ) {
                sname  = keys(skill_status);
                for( i=0; i<sizeof(skill_status); i++ ) {
                        command("enable unarmed "+sname[i]);
                        command("enable force "+sname[i]);
                        command("enable parry "+sname[i]);
                        command("enable dodge "+sname[i]);
                        if (stringp(skill1))
                                command("enable "+skill1+" "+sname[i]);
                        if (stringp(skill2))
                                command("enable "+skill2+" "+sname[i]);
                }
        }

        command("enforce max");

        //delete("fighting", me);
        //set("backup/condition", ob->query_condition(), me);
        set("auto_perform", 1);
        set("no_suck", 1);
        set("env/wimpy", 0);
        save();
        tell_object(ob, "状态储存完毕。\n");

        return 1;
}

void self_adjust (object me)
{
        mapping skill_status;
        string *skillnames;
        int i;

        set("max_jing", 600, me);
        set("eff_jing", 600, me);
        set("jing", 600, me);
        set("max_qi", 600, me);
        set("eff_qi", 600, me);
        set("qi", 600, me);
        set("neili", 600, me);
        set("max_neili", 600, me);
        set("jiali", 60, me);
        set("combat_exp", 100, me);

        skill_status = me->query_skills();
        if ( mapp(skill_status) )
        {
                skillnames = keys(skill_status);
                for(i=0; i<sizeof(skillnames); i++)
                        me->set_skill(skillnames[i], 60);
        }
        carry_object("/clone/misc/cloth")->wear();
        me->save();
}

string zm_apply()
{
        object me = this_object();
        object ob = this_player();

        if( query("family/family_name", me) != query("family/family_name", ob) )
                return "我便是"+query("family/family_name", me)+"首席大弟子！\n";

        if( query("betrayer", ob) || query("detach/"+query("family/family_name", me), ob) )
                return "你曾叛师欺祖，言无信行不轨，岂能出任首席大子弟一职！\n";

        if( query("current_player", me) == query("id", ob) )
                return "你又糊涂了！\n";

        if( query("family/gongji", ob) < 1000 )
                return "挑战首席大弟子需要1000点门派功绩。\n";

        if( me->is_fighting() || query("fighting", me) )
                return "已经有人正在挑战首席大弟子！\n";

        addn("family/gongji", -1000, ob);
        tell_object(ob, HIC"你使用1000点门派功绩换取挑战门派首席大弟子。\n"NOR);

        set_temp("zm_applied", 1, ob);
        do_recopy (me); // copy 玩家状态
        full_self();
        ob->fight_ob(me);
        me->fight_ob(ob);
        competition_with(ob);
        delete_temp("zhangmen/kill", me);
        return "好！你有意出任首席大弟子一职？我们就切磋一下吧！\n";
}

int do_recopy (object me)
{
        string player_name;
        object current_player;


        player_name = query("current_player", me);
        if( !player_name || player_name == "none of us" ) return 1;
        
        current_player = UPDATE_D->global_find_player(player_name); 
        if( !objectp(current_player) ) 
                return 1;
        
        if( query("combat_exp", current_player) > query("combat_exp", me) )
                do_clone (me, current_player);
                        
        UPDATE_D->global_destruct_player(current_player, 1); 

        return 1;
}

void win()
{
        object me = query_competitor();

        if( !objectp(me) ) {
                command("heihei");
                return;
        }

        command("say 看来" + RANK_D->query_respect(me) +
                "还得多加练习，方能在当今武林中出人头地 !\n");
        ::win();
}

void lost()
{
        object me, ob, who;

        me = this_object();
        ob = query_competitor();

        if( !living(me) ) me->revive();
        me->full_self();
        set("fighting", 1, me);
        message_vision ("$N翻身下拜，连声佩服！\n",me);
        if( query_temp("zhangmen/kill", me) && query_temp("zm_applied", ob) )
        {
                message_vision ("$N皱了皱眉道：此次比武我未能静心尽力，希望重新来过。\n", me);
                return ::lost();
        }
        
        if( !query_temp("zm_applied", ob) ) return ::lost();
        
        if( query("current_master", me) )
                who = present(query("current_master", me), environment(me));
        
        if( objectp(who) )
        {
                call_out("master_announce",1, me, who, ob);
         
        }
        else
        {
                message_vision("$N躬身对$n道：恭请拜见师父。\n",me,ob);
                command("follow "+query("id", ob));
                if( !query("where", me) )
                        set("where", base_name(environment(me)), me);
                remove_call_out("find_master");
                call_out("find_master", 1, me, ob);
                remove_call_out("time_out");
                call_out("time_out", 60, me, ob);
        }
        ::lost();
}

void time_out (object me, object ob)
{
        if( !query("fighting") ) return;
        if( objectp(ob) && same_environment(me, ob) )
                message_vision ("$N很不高兴的对$n说道，让你带我一起去拜见掌门，你墨迹到现在也没有去，如此还是算了吧！\n\n",me,ob);
        else if( objectp(ob) )
                tell_object(ob, "首席大弟子很不高兴的传话给你，让你带他一起去拜见掌门，你墨迹到现在也没有去，如此还是算了吧！\n");
        else
                message_vision ("$N奇怪的朝周围看了看，喃喃道：人呢？如此还是算了吧！\n\n",me);
        
        delete("fighting");
        me->set_leader(0);
        remove_call_out("find_master");
        me->move(query("where", me));
}

void find_master (object me, object ob)
{
        object who = present(query("current_master", me), environment(me));
        
        if( !living(me) ) me->revive();
        me->full_self();
        if( !objectp(who) )
        {
                remove_call_out("find_master");
                call_out("find_master", 1, me, ob);
        }
        else
        {
                message_vision ("$N见了师父赶紧下拜，又抬起头朝$n使了个眼色。\n\n",me,ob);
                message_vision ("$N微微地点了点头。\n\n",who);
                message_vision ("$N退下。\n\n",me);
                me->set_leader(0);
                call_out("master_announce",1,me,who,ob);
                me->move(query("where", me));
        }
}

void master_announce (object me, object who, object ob)
{
        object ling;
        
        remove_call_out("time_out");
        if( !living(me) ) me->revive();
        me->full_self();
        CHANNEL_D->do_channel(who, "chat","本派首席大弟子"+query("name", ob)+"今日走马上任。恭请各位大侠多加捧场！");
        delete_temp("zm_applied", ob);
        set("new_player", 1, me); // npc
        delete("fighting", me);
        convert_identity(me, ob);

        if( !query("xkd/ling", ob) )
        {
                seteuid(getuid());
                ling = new( "/d/xiakedao/obj/tongpai1" );
                set("own",query("id",  ob), ling);
                ling->move( ob );
                ling = new( "/d/xiakedao/obj/tongpai2" );
                set("own",query("id",  ob), ling);
                ling->move( ob );
                message_vision( HIY"$N对$n说道：侠客岛昨日送来赏善罚恶令，邀请为师上岛。\n                你是本门首席大弟子，就代为师走一趟吧。\n"NOR, who, ob );
                message_vision( HIC"说完，$N把两块令牌交到$n手里。\n"NOR, who, ob );
                set("xkd/ling", 1, ob);
                set("xkd/time", time()+86400, ob);
        }
}

int convert_identity (object me, object ob)
{
        object who;
//      string err;

        who = UPDATE_D->global_find_player(query("current_player", me)); 
        if( objectp(who) )
        {
                if( who->query_family() == ob->query_family() && query("zhangmen/title_old", who) )
                        set("title",query("zhangmen/title_old",  who), who);
                else if( query("family/family_name", who) )
                {
                        set("title", sprintf("%s第%s代%s",
                                        query("family/family_name", who),
                                        chinese_number(query("family/generation", who)),
                                        query("family/title", who)), who);
                }
                delete("family/first", who);
                who->save();
                UPDATE_D->global_destruct_player(who, 1); 
        }
        
        set("zhangmen/base_name", base_name(me), ob);
        set("zhangmen/data_name", me->query_save_file(), ob);
        set("zhangmen/title_old",query("title",  ob), ob);
        set("zhangmen/title",query("family/family_name",  ob)+zname(ob), ob);
        set("title",query("family/family_name",  ob)+zname(ob), ob);
        set("family/first", 1, ob);

        me->reset_me(me); // 恢复初始状态
        set("name",query("name",  ob), me);
        set("gender",query("gender",  ob), me);
        set("current_player",query("id",  ob), me);
        set("title",query("family/family_name",  ob)+zname(ob), me);
        set("short",query("name", me) + "("+capitalize(query("id", me))+")", me);
        do_clone(me,ob);
        return 1;
}

string query_save_file()
{
        string str = query("save_file");
//      int i;

        if (str) return str;
        str = DATA_DIR+"zhangmen/"+query("current_master");
        str = replace_string(str," ","_");
        return str;
}

void set_save_file(string str)
{
        set("save_file", str);
}

void kill_ob(object ob)
{
        object me = this_object();
        object master;

        if( query("current_master", me) )
                master = present(query("current_master", me), environment(me));
        if( objectp(master) ) master->kill_ob(ob);
        set_temp("zhangmen/kill", 1, me);
        ::kill_ob(ob);
}

string zname(object ob)
{
        return "首席大弟子";
        if( query("gender", ob) == "女性") return "首席大师姐";
        else return "首席大师兄";
}

void reset_me (object me)
{
        int i;
        object *inv;
        mapping skill_status, map_status ,prepare_status;
        string *skillnames, *mapnames , *pname;

        if ( mapp(map_status = me->query_skill_map()) )
        {
                mapnames = keys(map_status);
                for(i=0; i<sizeof(mapnames); i++)
                {
                        me->map_skill(mapnames[i]);
                }
        }

        if ( mapp(skill_status = me->query_skills()) )
        {
                skillnames = keys(skill_status);
                for(i=0; i<sizeof(skillnames); i++)
                {
                        me->delete_skill(skillnames[i]);
                }
        }

        if ( mapp(prepare_status = me->query_skill_prepare()) )
        {
                pname = keys(prepare_status);

                for(i=0; i<sizeof(prepare_status); i++)
                {
                        me->prepare_skill(pname[i]);
                }
        }

        inv = all_inventory(me);
        for( i=0; i<sizeof(inv); i++ )
                destruct (inv[i]);

        set("title", query("family/family_name", me) + zname(me), me);
        set("short", query("name", me) + "("+capitalize(query("id", me))+")", me);

        me->set_skill("force",  60);
        me->set_skill("unarmed",60);
        me->set_skill("sword",  60);
        me->set_skill("dodge",  60);
        me->set_skill("parry",  60);

        set("max_jing", 600, me);
        set("eff_jing", 600, me);
        set("jing", 600, me);
        set("max_qi", 600, me);
        set("eff_qi", 600, me);
        set("qi", 600, me);
        set("neili", 600, me);
        set("max_neili", 600, me);
        set("jiali", 30, me);
}

int accept_hit(object me)
{
        command("say 我是堂堂首席大弟子！要切磋你找别人去。\n");
        return 0;
}

int accept_fight(object who)    { return accept_hit(who); }
int accept_kill(object who)     { return accept_hit(who); }
int accept_ansuan(object who)   { return accept_hit(who); }
int accept_touxi(object who)    { return accept_hit(who); }

varargs void unconcious(object defeater) 
{
        ::unconcious();

        if( !living(this_object()) ) this_object()->revive();
}