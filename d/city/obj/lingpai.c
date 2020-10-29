#include <ansi.h>
inherit ITEM;
//inherit F_CLEAN_UP;
void kf_same(object who,object me);

void setup()
{}

void init()
{
        add_action("do_watch","guancha");
        add_action("do_watch","watch");
        add_action("do_catch","daibu");
        add_action("do_catch","catch");
}
int is_container() { return 1; }


void create()
{
        set_name("令牌", ({"ling pai","ling" }));
       set_max_encumbrance(10);
       set("unit", "块");
       set("long", "这是一块朱红的令牌,精钢打造，用来证明官府人士的身份。\n带着它你就有权搜寻罪犯(guancha)，逮捕嫌疑犯(daibu)。\n");
       set("value", 0);
       set("no_drop", "这样东西不能离开你。\n");
       set("no_burn",1);
       set("no_get", "这是朝廷的东西，平常人拿了会惹麻烦的。\n");
       set_weight(200);
       set("place","on");

       setup();
}
int do_watch(string arg)
{
        object obj,new_obj;
        object me = this_player();
        object ob = this_object();
        string targ;
        if( !query("kaifengfu", me) )
                return notify_fail("你并非朝廷官员，何必操这份闲心？\n");
        if (!ob=present("ling pai",me))
                return notify_fail("什么？\n");
        if( query_temp("kf_finish", me) )
                return notify_fail("程药发等着回话哪，你还在磨蹭什么？\n");
        if (!arg||!obj=present(arg,environment(me)))
                return notify_fail("你要观察谁？\n");
        if( !obj->is_character() || obj->is_corpse() )
        return notify_fail("你只能观察一个活的物体。\n");
        if( me->is_busy() )
                return notify_fail("你正忙着。\n");
        targ=query("name", obj);
        tell_object(me,"你用锐利的眼神盯着"+targ+"。\n\n");

        if( query_temp("kf_tufei", obj) == query_temp("kf_npc", me )
         && random(query("kar", me))>15){
                switch(random(5)) {
                case 0:
                        tell_object(me,WHT"你发现"+targ+"忽然把头一低，似乎想避开你的目光。\n\n"NOR);
                     break;
                case 1:
                        tell_object(me,WHT"你发现"+targ+"忽然打了个哆嗦，面如土色。\n\n"NOR);
                        break;
                case 2:
                        tell_object(me,WHT"你发现"+targ+"太阳穴高高坟起，似乎是个练武的人。\n\n"NOR);
                        break;
                case 3:
                        tell_object(me,WHT"你发现"+targ+"腰间鼓鼓囊囊的，样子象是一件兵刃。\n\n"NOR);
                        break;
                case 4:
                        tell_object(me,WHT"你发现"+targ+"的眼中精光一闪，马上又变的一脸茫然。\n\n"NOR);
                        break;
                }
                set_temp("kf_faxian", 1, me);
                set_temp("kf_faxianed",query("id",  me), obj);

                }  
        else{
                switch(random(11)) {
                        case 0:
                        tell_object(me,"只见"+targ+"正挤眉弄眼，色迷迷的东张西望。\n\n");
                        break;
                        
                        case 1:
                        tell_object(me,"只见"+targ+"饿得面黄肌瘦，骨瘦如柴。\n\n");
                        break;
                        
                        case 2:
                        tell_object(me,"只见"+targ+"面颊微红，一脸娇羞的模样。\n\n");
                     break;
                
                        case 3:
                        tell_object(me,"只见"+targ+"满脸横肉，嘴脸凶顽。\n\n");
                        break;
                        
                        case 4:
                        tell_object(me,"只见"+targ+"悲痛欲绝，哭的象个泪人似的。\n\n");
                        break;

                        case 5:
                        tell_object(me,"只见"+targ+"手足僵硬，浑身散发着金属光泽。\n\n");
                        break;

                        case 6:
                        tell_object(me,"只见"+targ+"面无表情，呆若木鸡。\n\n");
                        break;
                        
                        case 7:
                        tell_object(me,"只见"+targ+"长得尖嘴猴腮，目光狡诈。\n\n");
                        break;
         
                        case 8:
                        tell_object(me,"只见"+targ+"干笑几声，脸上挤出一丝媚笑。\n\n");
                        break;
                
                        case 9:
         
                        tell_object(me,"只见"+targ+"挺胸叠肚，一脸傲慢的神色。\n\n");
                     break;
                
                        case 10:
                        tell_object(me,"只见"+targ+"长得明眸皓齿，一脸天真的神色。\n\n");
                        break;
                }
        }
        return 1;
}

int do_catch(string arg)
{
        object obj,new_obj;
        object me = this_player();
        object ob = this_object();                        //100
        if (!ob=present("ling pai",me))
                return notify_fail("什么？\n");
        if( !query("kaifengfu", me) )
                return notify_fail("你并非朝廷官员，何必操这份闲心？\n");
        if( query_temp("kf_finish", me) )
                return notify_fail("林大人等着回话哪，你还在磨蹭什么？\n");
        if (!arg||!obj=present(arg,environment(me)))
                return notify_fail("你要逮捕谁？\n");
        if( !obj->is_character() || obj->is_corpse() )
                return notify_fail("你只能逮捕一个活人。\n");
        if( !query_temp("kf_faxian", me )
         || query_temp("kf_faxianed", obj) != query("id", me) )
                return notify_fail("朝廷纪律严明，没有证据怎好拿人？\n");
        message_vision ("$N对着$n冷笑一声道：阁下的案子发了，老老实实跟本官走一趟。\n\n",me,obj);
        if( query_temp("kf_whatnpc", me) == 1)new_obj=new("/d/kaifeng/npc/tufei1.c");
    if( query_temp("kf_whatnpc", me) == 2)new_obj=new("/d/kaifeng/npc/tufei2.c");
    if( query_temp("kf_whatnpc", me) == 3)new_obj=new("/d/kaifeng/npc/tufei3.c");
    if( query_temp("kf_whatnpc", me) == 4)new_obj=new("/d/kaifeng/npc/tufei4.c");
    if( query_temp("kf_whatnpc", me) == 5)new_obj=new("/d/kaifeng/npc/tufei5.c");
    if( query_temp("kf_whatnpc", me) == 6)new_obj=new("/d/kaifeng/npc/tufei6.c");
    if( query_temp("kf_whatnpc", me) == 7)new_obj=new("/d/kaifeng/npc/tufei7.c");
    if( query_temp("kf_whatnpc", me) == 8)new_obj=new("/d/kaifeng/npc/tufei8.c");
        message_vision (RED"$n大叫一声揭开伪装，露出本来面目。\n"NOR,me,obj);
//      destruct(obj);
        delete_temp("kf_faxianed", obj);
//       new_obj = present("picture",ob);
        kf_same(new_obj,me);    
       new_obj->move(environment(me));    
        message_vision (RED"$n大喝道：老子和你拼了！\n"NOR,me,new_obj);
       new_obj->kill_ob(me);
       me->kill_ob(new_obj);
       new_obj->set_leader(me);
       set_temp("kf_npc",query_temp("kf_npc",  me), new_obj);
       set_temp("kf_ownname",query("id",  me), new_obj);
       delete("no_see", new_obj);
       new_obj->start_busy(1);
       delete_temp("kf_faxian", me);
//      me->set_temp("kf_finish");
       return 1;
}

void kf_same(object who,object me)
{
        mapping myscore;
        int maxskill;
        myscore = me->query_entire_dbase();
        set("combat_exp",query("combat_exp",  me)*10/7, who);

        set("max_qi", myscore["max_qi"], who);
        set("eff_qi", myscore["eff_qi"], who);
        set("qi", myscore["max_qi"], who);

        set("max_jing", myscore["max_jing"], who);
        set("eff_jing", myscore["eff_jing"], who);
        set("jing", myscore["max_jing"], who);

          set("max_neili", myscore["max_neili"], who);
        set("neili", myscore["max_neili"], who);
        set("jiali", 0, who);
        maxskill = me->query_skill("force",1);
        if(maxskill < me->query_skill("parry",1)) maxskill=me->query_skill("parry",1); 
        if(maxskill < me->query_skill("dodge",1)) maxskill=me->query_skill("dodge",1); 
        if(maxskill < me->query_skill("sword",1)) maxskill=me->query_skill("sword",1); 
        if(maxskill < me->query_skill("blade",1)) maxskill=me->query_skill("blade",1); 
        if(maxskill < me->query_skill("unarmed",1)) maxskill=me->query_skill("unarmed",1); 
        set("maxskill", maxskill, who);

}