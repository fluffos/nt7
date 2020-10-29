inherit NPC;
int do_copy(object me);

string *sword_skill = ({ 
"taiji-jian","damo-jian","fumo-jian","jinshe-jian","yuxiao-jianfa",
"yunv-jian","murong-jianfa","huashan-sword", "duanjia-jian",
"huifeng-jian","liangyi-jian","quanzhen-jian" }); 

string *blade_skill = ({ 
"cibei-dao","fanliangyi-dao","liuhe-dao","murong-daofa",
"xiuluo-dao","xuanxu-dao", "yanxing-dao",}); 

string *staff_skill = ({ "wuchang-zhang","fengmo-zhang","tianshan-zhang" }); 

string *club_skill = ({ "zui-gun","weituo-gun" }); 

string *whip_skill = ({ "canglang-bian" }); 

string *dodge_skill = ({ 
"suibo-zhuliu", "yunv-shenfa","zhaixing-gong","xiaoyaoyou","huashan-shenfa","tiyunzong" }); 

string *weapon_list = ({ "chui","sword","blade","whip","gun","sword","gangzhang","blade" }); 

string *first_name = ({ "蒙面客","黑衣人","神秘人","黑衣忍者","山贼","探子","死士" }); 

void create()
{
        string s_sword,s_blade,s_club,s_whip,s_staff,s_dodge, weapon, name;        
        name = first_name[random(sizeof(first_name))];
        s_sword = sword_skill[random(sizeof(sword_skill))];
        s_blade = blade_skill[random(sizeof(blade_skill))];
        s_club  = club_skill[random(sizeof(club_skill))];
        s_whip  = whip_skill[random(sizeof(whip_skill))];
        s_staff = staff_skill[random(sizeof(staff_skill))];
        s_dodge = dodge_skill[random(sizeof(dodge_skill))];
        weapon = weapon_list[random(sizeof(weapon_list))];

        set_name(name, ({ "attacker"}));
        set("gender", "男性");
        set("age", 20 + random(40));
        set("long", "这家伙一付凶神恶煞的模样，时不时发出邪恶的阴笑。\n");
        set("combat_exp", 20000);
        set("attitude", "peaceful");
        set("str", 30);
        set("int", 22);
        set("con", 24);
        set("dex", 25);
        set("max_qi", 400);
        set("max_jing", 400);
        set("neili", 600);
        set("max_neili", 600);
        set("jiali", 10);
        set_skill("changquan", 30);
        set_skill("unarmed", 30);
        set_skill("force", 30);
        set_skill("taiji-shengong", 30);
        set_skill("sword", 30);
        set_skill("parry", 30);
        set_skill("dodge", 30);
        set_skill("blade", 30);
        set_skill("hammer", 30);
        set_skill("club", 30);
        set_skill("staff", 30);
        set_skill("whip", 30);
        set_skill(s_sword, 30);
        set_skill(s_blade, 30);
        set_skill(s_club, 30);
        set_skill(s_whip, 30);
        set_skill(s_staff, 30);
        set_skill(s_dodge, 30);
        map_skill("force", "taiji-shengong");
        map_skill("sword", s_sword);
        map_skill("dodge", s_dodge);
        map_skill("parry", "changquan");
        map_skill("blade", s_blade);
        map_skill("club", s_club);
        map_skill("whip", s_whip);
        map_skill("staff", s_staff);
        map_skill("unarmed", "changquan");       
        setup();
        add_money("silver", random(10));
}        
                
void unconcious()
{    
        tell_room(environment(this_object()),query("name", this_object())+"转身几个起落就不见了。\n",({this_object()}));
        destruct(this_object());        
}

int do_copy(object me)
{
        object ob, weapon;
        string my_id, type, type1;
        int i;
        ob = this_object();

        if(!me) ob->unconcious();
        my_id=query("id", me);
        weapon=query_temp("weapon", ob);
          
        i = me->query_skill("dodge",1) - (10 + random(40));
        if( query("jiuyang", me))i=query("max_pot", me)-100;
        if(i < 30) i = 30;
        set("combat_exp",query("combat_exp",  me)/5*4, ob);
        if(weapon) {
           type=query("skill_type", weapon);
           type1 = ob->query_skill_mapped(type);
           ob->set_skill(type, i);
           ob->set_skill(type1, i);
        }
        ob->set_skill("force", i);
        ob->set_skill("cuff", i);
        ob->set_skill("dodge", i);
        ob->set_skill("parry", i);
        ob->set_skill(ob->query_skill_mapped("dodge"), i);
        ob->set_skill("xinyuegong", i);  
        ob->set_skill("taiji-shengong", i);     
        ob->set_skill("taizuquan", i); 
        set("max_qi",query("max_qi",  me)/3*2, ob);
        set("max_jing",query("max_jing",  me)/3*2, ob);
        set("max_neili",query("max_neili",  me)/3*2, ob);
        set("jiali", ob->query_skill("force")/3, ob);
        ob->reincarnate(); 
        set("eff_jing",query("eff_jing",  me)/3*2, ob);
        set("jingli",query("jingli",  me)/3*2, ob);
        set("neili",query("max_neili",  me)/3*2, ob);
        set("qi",query("max_qi",  me)/3*2, ob);
        command("stare"+query("id", me));
        remove_call_out("checking");
        call_out("checking", 1, me, ob);
        set("victim",query("id",  me), ob);
        return 1;
}

int checking(object me, object ob)
{
        if(!ob) return 0;
    if(!me || environment(me)!= environment(ob)) ob->unconcious();
    if(!ob) return 0;
        if(ob->is_fighting()){
          call_out("checking", 1, me, ob);
          return 1;
        }
        else if( !ob->is_killing(query("id", me))){
          ob->kill_ob(me);
          call_out("checking", 1, me, ob);
          return 1;
        }
        else ob->unconcious();
        return 1;
}

int accept_fight(object victim)
{
        command("say 你这是找死！");
        kill_ob(victim);
        return 1;
}
