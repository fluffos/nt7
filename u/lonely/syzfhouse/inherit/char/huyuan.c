// /inherit/char/huyuan.c 屋宅护院的继承文件
// By Alf, Last Update 2003.0718

#include <ansi.h>
#include <command.h>

inherit CHARACTER;
inherit F_CLEAN_UP;
inherit F_SAVE;

int ask_vip();
int ask_level();
int ask_faction();
int ask_all_faction();
int do_shenji(string arg);
int setskills(string arg);
int do_modify(string arg);
int add_guest(string arg);
void do_action();
void add_all_action();
void add_all_settings();
object carry_object(string file);

int is_house_huyuan()
{
    return 1;
}

void init()
{
    if(this_player()->query("id") == query("owner"))
    {
        add_all_action();
    }
    ::init();
}

void add_all_action()
{
    add_action("do_shenji", "shengji");
    add_action("do_modify", "modify");
    add_action("add_guest", "setvip");
    add_action("setskills", "setskill");
}

void add_all_settings()
{
    int i;
    mapping *all_skill, all_inquiry;

    all_inquiry = ([]);
    all_skill   = FACTION_D->query_all_skill();
    for(i = 0; i < sizeof(all_skill); i++)
    {
        all_inquiry += ([ all_skill[i]["name"] : (: ask_faction :)]);
    }

    all_inquiry += ([
        "客人"     : (: ask_vip :),
        "贵宾"     : (: ask_vip :),
        "vip"      : (: ask_vip :),
        "guest"    : (: ask_vip :),
        "升级"     : (: ask_level :),
        "等级"     : (: ask_level :),
        "级别"     : (: ask_level :),
        "level"    : (: ask_level :),
        "faction"  : (: ask_faction :),
        "menpai"   : (: ask_faction :),
        "门派"     : (: ask_faction :),
        "武功"     : (: ask_faction :),
        "技能"     : (: ask_faction :),
        "武功等级" : (: ask_faction :),
        "技能等级" : (: ask_faction :),
        "武功级别" : (: ask_faction :),
        "技能级别" : (: ask_faction :),
        "skill"    : (: ask_faction :),
        "skills"   : (: ask_all_faction :),
        "武功总览" : (: ask_all_faction :),
        "门派总览" : (: ask_all_faction :),
        "技能总览" : (: ask_all_faction :),
    ]);

    this_object()->set("inquiry", all_inquiry);
    this_object()->set("chat_chance_combat", 100);
    this_object()->set("chat_msg_combat",
    ({
        (: do_action :),
    }));

    if(query("carry_obj/armor"))
        carry_object(query("carry_obj/armor"))->wear();
    if(query("carry_obj/weapon"))
        carry_object(query("carry_obj/weapon"))->wield();
    if(query("carry_obj/horse"))
        carry_object(query("carry_obj/horse"))->ride();
}

void unconcious()
{
    int i;
    object me, room;
    string path, *file;

    me = this_object();
    path = me->query("path");
    if(!path || base_name(environment(me)) != me->query("startroom"))
    {
        ::unconcious();
        return;
    }

    file = get_dir(path + "/");
    for(i = 0; i < sizeof(file); i++)
    {
        room = get_object(path + "/" + file[i]);
        if(room == environment(me))
        {
            tell_room(room, me->name(1) + "惨呼一声：“主....人，"
                                          "来闯的点子太硬，我、我"
                                          "挡不住了......\n\n");
            continue;
        }
        tell_room(room, HIR "\n门外忽然传来" + me->name(1) +
                            "的一声闷哼：“主....人，来闯的点子"
                            "太硬，我、我挡不住了......\n\n" NOR);
    }
    ::unconcious();
}

int ask_vip()
{
    return HOUSE_D->ask_guest(this_player(), this_object());
}

int ask_level()
{
    return HOUSE_D->ask_huyuan_level(this_player(), this_object());
}

int ask_faction()
{
    this_player()->set_temp("query_faction", 1);
    return HOUSE_D->ask_huyuan_faction(this_player(), this_object());
}

int ask_all_faction()
{
    this_player()->set_temp("ask_all_faction", 1);
    return HOUSE_D->ask_huyuan_faction(this_player(), this_object());
}

int do_shenji(string arg)
{
    return HOUSE_D->shenji_huyuan(arg, this_player(), this_object());
}

int setskills(string arg)
{
    return HOUSE_D->set_huyuan_skill(arg, this_player(), this_object());
}

int do_modify(string arg)
{
    return HOUSE_D->modify_huyuan(arg, this_player(), this_object());
}

int add_guest(string arg)
{
    return HOUSE_D->add_guest(arg, this_player(), this_object());
}

object carry_object(string file)
{
    object ob;
    if(!objectp(ob = new(file)))
        return 0;
    ob->move(this_object());
    return ob;
}

string query_save_file()
{
    string file = base_name(this_object());
    return DATA_DIR + file;
}

int save()
{
    string file;

    if(stringp(file = this_object()->query_save_file()))
    {
        assure_file(file + __SAVE_EXTENSION__);
        return save_object(file);
    }
    return 0;
}

int restore()
{
    string file;

    if(stringp(file = this_object()->query_save_file())
        && file_size(file + __SAVE_EXTENSION__) > 0 )
    {
        restore_object(file);
        this_object()->set("qi", this_object()->query("max_qi"));
        this_object()->set("jing", this_object()->query("max_jing"));
        this_object()->set("eff_qi", this_object()->query("max_qi"));
        this_object()->set("eff_jing", this_object()->query("max_jing"));
        this_object()->set("jingli", this_object()->query("max_jingli"));
        this_object()->set("neili", this_object()->query("max_neili"));
        return 1;
    }
    return 0;
}

int accept_fight(object who)
{
    if(!this_object()->is_livings())
        return 0;

    if(query("type") == "bang")
    {
        if(this_player()->query("bang/name") == query("owner_name"))
        {
	        message_vision("$N对$n摇头道：“您是在开玩笑吧？在下可不敢与您动手！”\n",
	                        this_object(), this_player());
	        return 0;
        }
    }
    else
        if(query("type") == "user" || query("type") == "xian")
    {
        if(this_player()->query("id") == query("owner")
            || this_player()->query("couple/couple_id") == query("owner"))
        {
	        message_vision("$N对$n摇头道：“您是在开玩笑吧？在下可不敢与您动手！”\n",
	                        this_object(), this_player());
	        return 0;
        }
    }

    if(base_name(environment(this_object())) == this_object()->query("startroom"))
    {
	    message_vision("$N朝$n怒喝道：“你敢打这里的主意！有我在，"
	                   "就由不得你撒野！”\n", this_object(), this_player());
	}

	this_object()->exert_function("powerup");
	kill_ob(this_player());
	return 1;
}

int accept_hit(object who)
{
    return accept_fight(this_player());
}

int accept_kill(object who)
{
    return accept_fight(this_player());
}

int accept_touxi(object who)
{
    return accept_fight(this_player());
}

int chat()
{
    if(!environment())
        return 0;
    if(!this_object()->is_livings())
        return 0;

    if(this_object()->is_fighting() && random(100) <= 50)
        return evaluate(do_action());
    return 1;
}

int exert_function(string func)
{
    string force_skill;

    if(stringp(force_skill = query_skill_mapped("force")))
        SKILL_D(force_skill)->exert_function(this_object(), func);
}

int perform_action(string action)
{
    object weapon;
    string martial_skill, act;

    if(sscanf(action, "%s.%s", martial_skill, act) != 2)
        return 0;

    martial_skill = query_skill_mapped(martial_skill);
    if(stringp(martial_skill))
        return SKILL_D(martial_skill)->perform_action(this_object(), act);
}

void do_action()
{
    int i, j, qi, eff_qi, flag = 0;
    object me, weapon;
    mapping prepare;
    string type, skill, *all_skill_file;
    string skill_dir, *perform_actions, action;

    me = this_object();
    if(me->query("qi") < me->query("eff_qi") * 3 / 5)
    {
        command("exert recover");
    }

    prepare = me->query_skill_prepare();
    weapon  = me->query_temp("weapon");
    if(objectp(weapon))
        type = weapon->query("skill_type");
    else
        if(sizeof(prepare) == 0)
            type = "unarmed";
    else
        if(sizeof(prepare) != 0)
            type = (keys(prepare))[0];

    if(!stringp(skill = me->query_skill_mapped(type)))
        return ;

    all_skill_file = get_dir("/kungfu/perform/");
    for(i = 0; i<sizeof(all_skill_file); i++)
    {
        if(all_skill_file[i] == skill)
        {
            skill_dir = all_skill_file[i];
            flag = 1;
            break;
        }
    }

    if(!flag)
        return;

    skill_dir = PFM_D(skill_dir+"/");
    perform_actions = get_dir(skill_dir);
    i = sizeof(perform_actions);
    if(!i)
        return;
    j = 0;
    while(j != 3)
    {
        action = perform_actions[random(i)];
        if(sscanf(action,"%s.c",action) == -1)
            continue ;
        if(me->perform_action(type + "." + action))
            j = 3;
        else
            j++;
    }
}

int return_home(object home)
{
    if(!environment() ||  environment() == home)
        return 1;
    if(!this_object()->is_livings() || is_fighting())
        return 0;
    message("vision", this_object()->name() + "急急忙忙地离开了。\n",
                                                       environment(),
                                                       this_object());
    return move(home);
}

