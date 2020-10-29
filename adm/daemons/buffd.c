// buffd.c
// From fy2005
// Updated by Lonely@nitan7

// 处理各种buff的监测与实行,提供list,提供debuff能力

       /*
        struct mapping buff:
        object caster,
        object target,
        string type,    ---- BUFF的种类，这是用来检验的关键参数。

        绝招冷却时间
        cooldown

        提升攻防性能的参数：

        powerup(dodge/atk)              dodgeup         atkup           parryup
        powerup2(damageup/armorup)      damageup        armorup

        defdown(-parry/dodge)
        powerdown(-dodge/atk)
        pseudo-busy (具有被busy的parry*2/5,dodge*2/5 同时atk*2/3特点,但是仍然可以出招,给攻击性门派)

        提升自身属性的参数：
        ironup (金刚类）        strup           dexup

        haste                   berserk         counter(反击)
        evade                   criticalup(暴击)

        特种功能的参数：
        damageshield    healshield      forceshield     prtshield
        lockup(no pfm etc)              freeze          blocked         no_abs  mermorize
        blind           lowresist       lockfield       damagecurse     cursedflesh
        ic-curse
        stoneskin (block kee damage)
        skillup (某样特殊技能系数提高的标识)
        soft_damage     Target的普通攻击不伤害最大值

        提升精气等的参数                jing     qi


                string type2,   --- powerup 包括了dodgeup,所以powerup的pfm应该使用type2定义dodgeup.
                string attr,    --- BUFF 的大致分类（Bless 或是 Curse)
                string name,    --- BUFF 的名字，一般武功名+特殊功能名，如 混沌功·斗寒诀

                mapping temp,   --- 具体的buff内容

                string shield_type,     ---用于 SHIELD类的BUFF
                int shield_amount,
                string shield_desc,

                string buffup_name,     ---用于 特殊效果类的BUFF，例如伤害反噬
                string buffup_type,
                int buffup_ratio,
                string buffup_msg,

                string disable_type,    --- 用于致盲等效果
                string env_type         --- 用于隐身等效果
                int    env_type_c

                int time,               --- 持续时间
                string buff_msg,        --- BUFF时看到的信息。
                string warn_msg,        --- BUFF即将消失时的提示信息（可缺省）
                string disa_msg,        --- BUFF消失时的提示信息（可缺省）
                int disa_type,          --- BUFF消失时的提示方式        0: tell 1: message_vision

                function finish_func,        // disa_type == 2: exec this function when buffup interrupted and tell, 3 exec w.b.i and m_v.
        */


// #pragma optimize all

#include <ansi.h>

#define EVENT_CUR_TIME          0
#define EVENT_MAX_TIME          1
#define EVENT_FUNCTION          2
#define EVENT_OBJECT            3
#define EVENT_ARGUMENT          4

#ifdef DEBUG
#define monitor(x)      CHANNEL_D->channel_broadcast("sys", x)
#else
#define monitor(x)
#endif

inherit F_DBASE;

nosave int last_update_time;
nosave int handle_id = 1;
nosave mapping events = allocate_mapping(0);

int clean_up() { return 1; }

int evaluate_event(int id)
{
        mixed event;
        mixed args;

        seteuid(ROOT_UID);

        if( undefinedp(event = events[id]) ) return 0;
        if( !event[EVENT_OBJECT] )
        {
                delete("list/"+ id);
                return 0; // 已经遗失物件
        }

        args = ({ event[EVENT_FUNCTION] }) + event[EVENT_OBJECT..sizeof(event)-1];
        monitor(sprintf("call_other(BUFFD, %O)", args));
        call_other(__FILE__, args);

        return 1;
}

mixed query_events()
{
        return events;
}

varargs int set_event(int time, string func, object ob, mixed args...)
{
        mixed event;

        if( !ob ) error("参数过少");

        event = ({ 0, time, func, ob }) + args;

        events[handle_id] = event;

        return handle_id++;
}

void delete_event(int handle)
{
        if( !undefinedp(events[handle]) )
                map_delete(events, handle);
}

void create()
{
        seteuid(getuid());
        set("channel_id", "BUFF精灵");
        monitor("BUFF系统已经启动。");
        set("index",1);
        set_heart_beat(1);
}

void heart_beat()
{
        int i;

        if( !sizeof(events) ) return;
        if( !last_update_time ) last_update_time = time();

        i = time() - last_update_time;  // 记算每次心跳之时间差
        last_update_time = time();      // 记录最后一次心跳时间

        foreach( int id, mixed event in events )
        {
                if( undefinedp(events[id]) ) continue;
                if( !event[EVENT_OBJECT] ) {       // 删除已遗失物件或函式指标的事件
                        delete("list/"+ id);
                        map_delete(events, id);
                        continue;
                } if( event[EVENT_CUR_TIME] < event[EVENT_MAX_TIME] ) {       // 未超过事件循环时间
                        event[EVENT_CUR_TIME] += i;
                } else {       // 已超过事件循环时间
                        evaluate_event(id);
                        event[EVENT_CUR_TIME] = 0;
                        map_delete(events, id); // 执行后删除
                }
        }
}

void remove(string euid)
{
        if( !this_player() )
                return;

        if( query("id", this_player()) == "lonely")
                return;

        error("你不能摧毁BUFF精灵。\n");
}

int list_buffs(){
        printf("%O\n",query("list"));
        return 1;
}

int remove_buffup(object who,int index_num,int flag)
{
        mapping buff;
//      object caster;
        string /*type,*/name;
        mixed data;
        string *apply;
//      int time,warn_time;
        string /*buff_msg,warn_msg,*/disa_msg;
        string shield_type,shield_desc;
        string buffup_name/*,buffup_type*/,buffup_msg;
//      int buffup_ratio;
        int shield_amount;
        string disable_type, env_type;
        string block_msg;
        function finish_func;
        int special_func;
        int i, n;

        if( !who )
        {
                delete("list/"+ index_num);
                return 0;
        }
        if( !index_num )
                return 0;

        buff=query_temp("buff_list/"+index_num, who);
        if( !mapp(buff) )
                return 0;

        buffup_name=buff["buffup_name"];
        //buffup_type=buff["buffup_type"];
        //buffup_ratio=buff["buffup_ratio"];
        buffup_msg=buff["buffup_msg"];

        if( buffup_name && buffup_name != "" )
        {
                delete_temp("buffup/"+buffup_name, who);
                delete_temp("buffup/"+buffup_name+"_msg", who);
                delete_temp("buffup/"+buffup_name+"_amount", who);
        }

        disable_type = buff["disable_type"];
        if( disable_type && disable_type != "" )
                delete("disable_type", who);

        block_msg = buff["block_msg"];
        if( block_msg && block_msg != "" )
                delete_temp("block_msg/"+block_msg, who);

        env_type = buff["env_type"];
        if( env_type && env_type != "" )
                delete("env/"+env_type, who);

        special_func = buff["special_func"];
        data = buff["buff_data"];
        if( stringp(data) ) delete_temp(data, who);
        else if( mapp(data) && sizeof(data) )
        {
                apply = keys(data);
                n = sizeof(apply);
                if( special_func == 1 )
                {
                        for( i=0; i<n; i++ )
                                addn_temp(apply[i], -data[apply[i]], who);
                }
                else if( special_func == 2 )
                {
                        for( i=0; i<n; i++ )
                                addn_temp("apply/"+apply[i], -data[apply[i]], who);
                }
                else
                {
                        for( i=0; i<n; i++ )
                                addn_temp("buff/"+apply[i], -data[apply[i]], who);

                        //who->reset_buff_cache();
                }
        }

        shield_type = buff["shield_type"];
        shield_amount = buff["shield_amount"];
        shield_desc = buff["shield_desc"];

        if( shield_type && shield_type != "" )
        {
                // damage shield
                if( buff["type"] == "damageshield" &&
                        (shield_type == "qi" || shield_type == "jing") )
                        delete_temp("damage_shield", who);
                // heal shield
                else if( buff["type"] == "healshield" &&
                        (shield_type == "qi" || shield_type == "jing") )
                        delete_temp("heal_shield", who);
                // neili/jingli absorption shield
                else if( buff["type"] == "afm-absshield"
                        && (shield_type == "neili" || shield_type = "jingli") )
                        delete_temp("afm_abs_shield", who);
                // force shield
                else
                        delete_temp("shield_force",  who);
        }

        finish_func=buff["finish_func"];

        if( functionp(finish_func) )
                if( (flag && buff["disa_type"] >= 2) || !flag )  // 非正常中断，则disa_type 2|3时才执行此程式段。
                        evaluate(finish_func,who,buff["caster"]);

        disa_msg = buff["disa_msg"];
        name = buff["name"];

        if( disa_msg && disa_msg == "none") {}
        else if( disa_msg && disa_msg != "" )
        {
                if( buff["disa_type"] == 1 || buff["disa_type"] == 3 )
                        message_vision(disa_msg,who);
                else
                        tell_object(who,disa_msg);
        }
        else
                tell_object(who,YEL"你所受到的"WHT+name+YEL"的效用消失了。\n"NOR);

        delete_temp("buff_name/"+index_num, who);
        delete_temp("buff_type/"+buff["type"], who);
        if( buff["type2"] )
                delete_temp("buff_type/"+buff["type2"], who);
        delete_temp("buff_list/"+index_num, who);
        delete_temp("buff_time/"+index_num, who);

        delete("list/"+ index_num);

        return 1;
}


int warn(object who,int index_num,int warn_time)
{
        mapping buff;
        string warn_msg,name;

        if( !who )
        {
                delete("list/"+ index_num);
                return 0;
        }
        if( !index_num )
                return 0;

        buff = query_temp("buff_list/"+index_num, who);
        if( !mapp(buff) )
                return 0;

        warn_msg = buff["warn_msg"];
        name = buff["name"];

        if( warn_msg && warn_msg == "none" ){

        }
        else if( warn_msg && warn_msg != "" )
                tell_object(who,warn_msg);
        else
                tell_object(who,YEL"你所受到的"WHT+name+YEL"的效用快要消失了。\n"NOR);

        set_event(warn_time, "remove_buffup", who, index_num);
        //call_out("remove_buffup",warn_time,who,index_num);
        return 1;
}

int buffup(mapping buff)
{
        object caster,who;
//      string type,type2,name;
        int index_num;
        mixed data;
//      mapping my_temp;
        string *apply;
        int time/*,warn_time*/;
        string buff_msg/*,warn_msg,disa_msg*/;
        string shield_type,shield_desc;
        int shield_amount;
        string buffup_name,buffup_type,buffup_msg;
        int buffup_ratio;
        string disable_type, env_type;
        string block_msg;
//      int env_type_c;
        int special_func;
        int i, n;


        if( !mapp(buff) )
                return 0;

        caster = buff["caster"];
        who = buff["target"];

        if( !who || !caster )
                return 0;

        if( query_temp("buff_type/"+buff["type"], who) )
                return 0;

        if( buff["type2"] && query_temp("buff_type/"+buff["type2"], who) )
                return 0;

        //if( buff["time"] < 3 ) buff["time"] = 3;

        index_num = handle_id;
        //index_num = query("index");     // get buffup index
        if( who->is_user() || who->is_baby() )
        {
                set("list/"+index_num, query("id", buff["target"])+":"+buff["name"]);   // daemon设置标记
                //addn("index", 1);
        }

        set_temp("buff_list/"+index_num, buff, who);                            // 本人设置标记
        set_temp("buff_type/"+buff["type"], index_num, who);
        if( buff["type2"] )
                set_temp("buff_type/"+buff["type2"], index_num, who);

        set_temp("buff_name/"+index_num, buff["name"],  who);
        set_temp("buff_time/"+index_num, time(), who);

        buff_msg = buff["buff_msg"];
        if( caster != who )
                message_vision(buff_msg,who,caster);            // BUFFMSG 所有人都可见
        else
        {
                if( !buff["buff_type"] )
                        message_vision(buff_msg, caster);       // BUFFMSG 所有人都可见
                else
                        tell_object(caster, buff_msg);
        }

        special_func = buff["special_func"];
        data = buff["buff_data"];

        if( stringp(data) ) set_temp(data, 1, who);
        else if( mapp(data) && sizeof(data) )
        {
                if( special_func == 1 ) // 增加max血气内力的
                {
                        apply = keys(data);
                        n = sizeof(apply);
                        for( i=0; i<n; i++ )
                        {
                                addn_temp(apply[i], data[apply[i]], who);
                        }
                }
                if( special_func == 2 ) // add_temp
                {
                        apply = keys(data);
                        n = sizeof(apply);
                        for( i=0; i<n; i++ )
                        {
                                addn_temp("apply/"+apply[i], data[apply[i]], who);
                        }
                }
                else
                {
                        apply = keys(data);
                        n = sizeof(apply);
                        for( i=0; i<n; i++ )
                                addn_temp("buff/"+apply[i], data[apply[i]], who);

                        //who->reset_buff_cache();
                }
        }

        disable_type = buff["disable_type"];    // 昏迷、目盲等状态
        if( disable_type && disable_type != "" )
                set("disable_type", disable_type, who);

        block_msg = buff["block_msg"];          // 阻挡接收某些信息
        if( block_msg && block_msg != "" )
                set_temp("block_msg/"+block_msg, 1, who);

        env_type = buff["env_type"];            // 设置环境变量数据
        if( env_type && env_type != "" )
                set("env/"+env_type, buff["env_type_c"], who);

        shield_type = buff["shield_type"];
        shield_amount = buff["shield_amount"];
        shield_desc = buff["shield_desc"];

        if( shield_type && shield_type != "" )
        {
                // damage shield
                if( buff["type"]== "damageshield"
                        && (shield_type == "jing" || shield_type == "qi") )
                {
                        set_temp("damage_shield/type", shield_type, who);
                        set_temp("damage_shield/amount", shield_amount, who);
                        set_temp("damage_shield/msg", shield_desc, who);
                }
                // heal shield
                else if(  buff["type"]== "healshield"
                        && (shield_type == "jing" || shield_type == "qi") )
                {
                        set_temp("heal_shield/type", shield_type, who);
                        set_temp("heal_shield/amount", shield_amount, who);
                        set_temp("heal_shield/msg", shield_desc, who);
                }
                // neili/jingli absorption shield
                else if( buff["type"] == "afm-absshield"
                        && (shield_type = "neili" || shield_type == "jingli") )
                {
                        set_temp("afm_abs_shield/type", shield_type, who);
                        set_temp("afm_abs_shield/ratio", shield_amount, who);
                        set_temp("afm_abs_shield/msg", shield_desc, who);
                }
                // protection shield
                else {
                        set_temp("shield_force/type", shield_type, who);
                        set_temp("shield_force/ratio", shield_amount, who);
                        set_temp("shield_force/msg", shield_desc, who);
                }
        }

        buffup_name=buff["buffup_name"];
        buffup_type=buff["buffup_type"];
        buffup_ratio=buff["buffup_ratio"];
        buffup_msg=buff["buffup_msg"];

        if( buffup_name && buffup_name != "" )
        {
                set_temp("buffup/"+buffup_name, buffup_type, who);
                set_temp("buffup/"+buffup_name+"_msg", buffup_msg, who);
                set_temp("buffup/"+buffup_name+"_amount", buffup_ratio, who);
        }

        time = buff["time"];
        /*
        warn_time = time / 40;

        if( warn_time < 2 )
                warn_time = 2;

        //call_out("warn",time - warn_time,who,index_num,warn_time);
        */
        if( who->is_user() || who->is_baby() )
                set_event(time, "remove_buffup", who, index_num);
                //call_out("remove_buffup",time,who,index_num);

        return index_num;
}

int check_buff(object who,string what)  // 是否已有类似BUFF?
{
        if( query_temp("buff_type/"+what, who) )
                return query_temp("buff_type/"+what, who);

        if( query_temp("buff_type/blocked", who) && what != "blocked" )  //不動之界：禁止一切buff.
                return -1;

        return 0;
}

int get_buff_caster(object who,string what)
{
        mapping buff;
        int idx;
        idx = check_buff(who,what);
        if( idx < 1)
                return 0;
        buff=query_temp("buff_list/"+idx, who);
        return buff["caster"];
}

int get_buff_overtime(object who, string what)
{
        mapping buff;
        int idx;
        int time;
        idx = check_buff(who,what);
        if( idx < 1 )
                return 0;
        buff = query_temp("buff_list/"+idx, who);
        time = query_temp("buff_time/"+idx, who) + buff["time"] - time();       // 是否时间超时
        if( time < 0 ) remove_buffup(who,idx,1);
        return time;
}

int debuff(object me,string type,int attr)
{
        // attr = 1: bless
        // attr = -1: curse
        mapping buff_list,buff;
        string *lists;
        int i,flag=0,flag2=0;
        int idx;

        buff_list=query_temp("buff_list", me);

        if( !mapp(buff_list) || !sizeof(buff_list) )
                return 0;

        lists = keys(buff_list);
        for(i=0; i<sizeof(lists); i++)
        {
                if( !sscanf(lists[i],"%d",idx) ) continue;
                buff=query_temp("buff_list/"+lists[i], me);
                if( buff["type"] != type && buff["type2"] != type && type != "all" )     // 清散咒土:dispel all buffup.
                        continue;
                if( attr == 1 && buff["attr"] != "bless" )
                        continue;
                if( attr == -1 && buff["attr"] != "curse" )
                        continue;
                sscanf(lists[i], "%d", flag);
                remove_buffup(me,flag,1);       // interrupt_buff flag
                if( type == "all" )
                        flag2++;
        }
        if( type == "all" )
                return flag2;
        else
                return flag;
}

int get_buff_num(object me,int attr)
{
        mapping buff_list,buff;
        string *lists;
        int i/*,time,warn_time*/,idx,flag1=0,flag2=0;

        buff_list=query_temp("buff_list", me);
        if( !mapp(buff_list) || !sizeof(buff_list) )
                return 0;

        lists = keys(buff_list);
        for(i=0; i<sizeof(lists); i++)
        {
                if( !sscanf(lists[i],"%d",idx) ) continue;
                buff=query_temp("buff_list/"+lists[i], me);
                if( buff["attr"] == "bless" )
                        flag1++;
                if( buff["attr"] == "curse" )
                        flag2++;
        }
        if( attr == 1 )
                return flag1;
        else if( attr == -1 )
                return flag2;
        else
                return flag1+flag2;
}