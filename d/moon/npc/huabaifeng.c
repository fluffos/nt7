#include <ansi.h>
//inherit "/d/taiping/npc/smart_npc";
inherit NPC;
void create()
{
        set_name("花白凤",({"hua baifeng","hua","baifeng"}));
        set("title",YEL"双手如鸡爪的老妇"NOR);
        set("long","
她脸上蒙着黑纱，黑色的长袍乌云般散落在地上，只露出一双干瘪、苍老、
鬼爪般的手。她双手合什，喃喃低诵，但却不是在析求上苍赐予多福，而
是在诅咒。诅咒着上苍，诅咒着世人，诅咒着天地间的万事万物。\n");
        
        set("gender","女性");
                
        set("age",32);          
        set("int",52);
        set("cor",30);
        set("cps",20);
        set("str",40);
        set("per",1);
        
        set_skill("unarmed",200);
        set_skill("dodge",150);
        set_skill("parry",160);
        set_skill("force",180);
        set_skill("move",200); 
        
        set("force",1500);
        set("max_force",1500);
        set("force_factor",120);
        set("max_atman",500);
        set("atman",500);
        set("max_mana",500);
        set("mana",500);
        set("combat_exp",1250000);  
        set("attitude", "friendly");
        
        set("resistance/kee",30);
        set("resistance/gin",30);
        set("resistance/sen",30);
                   
        
        setup();
        carry_object("/obj/armor/cloth")->wear();
//      carry_object(__DIR__"obj/gsword")->wield();    
    
} 
void init()
{       
        object me; 
        ::init();
        if( interactive(me = this_player()) && !is_fighting() ) {
                remove_call_out("greeting");
                call_out("greeting", 1, me);
        } 
          add_action("do_give", "show");
} 
void greeting(object me)
{
        object ob;
        ob=this_object();
        if( !me || environment(me) != environment() ) return;
        if (me->query("wanma/寻地洞") && !me->query("wanma/杀场主_ma")) {
                call_out("event1",1,me,0);      
        }
        if (me->query("m_success/神刀万马")) return;
        
        if (me->query("wanma/杀场主_ma")
                && me->query_temp("wanma/杀花满天_ma") && me->query_temp("wanma/杀云在天_ma")
                && me->query_temp("wanma/杀公孙断_ma") && me->query_temp("wanma/杀马芳玲_ma")
                && me->query_temp("wanma/杀小虎子_ma") 
                && !me->query("wanma/准备杀同伙_ma")) {        
                message_vision(CYN"
花白风点了点头，她的声音凄厉、尖锐，如寒夜中的鬼哭，“马空群，马
空群，你也有今天！”\n"NOR,ob);
                message_vision(CYN"
花白风说：“下一步，就轮到马空群的同伙了，我已经知道的有薛斌和易
大经，你要找出其余的，杀光他们的一家老少。”\n"NOR,ob);
                me->set("wanma/准备杀同伙_ma",1);
        }
        if (me->query("wanma/准备杀同伙_ma") 
                && me->query_temp("wanma/易大经_ma") && me->query_temp("wanma/薛斌_ma")
                && me->query_temp("wanma/桃花娘子_ma") && me->query_temp("wanma/柳东来_ma")
                /*&& me->query_temp("wanma/郭威_ma") */
                && !me->query("wanma/准备杀主脑_ma")) {
                message_vision(CYN"
花白风转过身去，跪在黑色的神龛前，喃喃低语，没有人能听到她在说什么，
片刻，。。\n"NOR,ob);
                me->set("wanma/准备杀主脑_ma",1);
        }       
        if (me->query("wanma/准备杀主脑_ma") && me->query_temp("wanma/杀马空群")
                && me->query_temp("wanma/杀丁白云") ){
                
                message_vision("$N向$n似哭似笑地大喊：终于报了。。。终于报了。。。\n",this_object(),me);
                message_vision("$N转过身去，再次跪在黑色的神龛前，喃喃低语，没有人能听到她在说什么，。。\n", this_object());
                if(!me->query("wanma/结局_ma")){
                                call_out("imbue_event", 2, me);
                        }
                if(!me->query("m_success/神刀万马"))
                {
                        me->set("m_success/神刀万马",1);
                        me->add("score",500);
                }
            }
        return;
} 
void die()
{
        object me, owner;
        if(objectp(me=query_temp("last_damage_from") ))     
        if(owner=me->query("possessed")) {
                me = owner;
        } 
me->set_temp("wanma/花白凤_ma",1);
        ::die();
}  
string *event1_msg=     ({
        CYN"
花白风冷冷地说：“是三娘指点你到这里的吧，我不管你的来历是什么，
只要你能为神刀堂报了这血海深仇，你就是神刀堂的传人。”\n"NOR, 
CYN"为了这一天，我已准备了十九年，整整十九年，傅红雪背叛了我，叶开背
叛了我，他们是背叛了神刀堂几十条屈死的冤魂！！！”\n"NOR, 
CYN"她的声音里充满了一种神秘的自信，仿佛已融入了天上地下所有神魔恶鬼
的诅咒。”\n"NOR, 
CYN"你要记住，从此以后，你就是神，复仇的神！无论你做什么，都用不着后
悔，无论你怎么样对他们，都是应当的！”\n"NOR, 
CYN"“不过，我绝不会让马空群死得太快，太容易，我要你先去杀了他的手下，
他的儿子女儿，让他尝尝家破人亡的滋味。\n"NOR, 
});  
void event1(object me, int count)
{
        if (environment(me)!=environment(this_object()) || this_object()->is_fighting()) return;
        tell_object(me,event1_msg[count]+"\n");
        if(++count==sizeof(event1_msg))
        {
                message_vision(CYN"花白风突又挥刀，一刀插入$N面前的土地上，厉声说道：“快走，用这把
刀将他们的头全都割下来，再回来见我，否则非但天要咒你，我也要咒你！\n\n\n"NOR,me);
                me->set("wanma/杀场主_ma",1);
                return;
        }
        else call_out("event1",1,me,count);
        return ;
}     

void imbue_event(object me){
        object weapon, *inv, obj;
        string prop;
   int i;
        if(!interactive(me) || environment(me) != environment(this_object())) {
                return 0;
        }
        obj = me->query_temp("weapon");
        if(objectp(obj) && obj->query("owner")) {
                weapon = me->query_temp("weapon");
        } else { 
                inv = all_inventory(me);        
                for(i=0; i<sizeof(inv); i++) {
                        if(inv[i]->query("weapon_prop") && inv[i]->query("owner")) {
                                weapon = inv[i];
                                break;
                        }
                }       
        }                       
        if(!objectp(weapon)){
                if(!objectp(obj)){
                        message_vision(HIC"\n咒语迷雾般缠绕着整个空间。。。\n"NOR, me);
                } else {
                        message_vision(HIC"\n咒语迷雾般缠绕着$N的" + obj->name() + HIC"上，然后再蒸腾，焕发。\n", me);
                }
        }else {
                message_vision(HIC"\n咒语迷雾般缠绕着$N的" + weapon->name() + HIC"上，一瞬间，让人恍然大悟。。。 \n"NOR,
                                me);
                message_vision(HIC"整个空间的力量似乎都集中在" + weapon->name() + HIC"上，但一下子就把所有的爱、恨、情、仇，一并带走。。。\n"NOR, me);
                if(weapon->query("weapon_prop")) {
                        prop="weapon_prop/";
                }
                if(weapon->query("equipped") == "wielded") {
                        weapon->unequip();
            
                         weapon->add(prop+"p_int", 10);
                   weapon->wield();
                } else {
          weapon->add(prop+"p_int", 10);
        }
                weapon->save();                 
                me->set("wanma/结局_ma", 1);
                if (me->query("class")=="bandit")
                	if (me->query_skill("tianya-blade",1)<1)
                me->set_skill("tianya-blade", 1);
                me->save();
                return;
        } 
        me->set("wanma/结局_ma", 2);
        me->save();
        return;
} 

int do_give(string arg){
        object ob,me,obj,rune;
        int i, j;
        string longarg,acceptor,objectname;
        mapping data, data2,spe_data, ench;
        string  *apply;
        
        obj = this_object();
        me = this_player();
      if (!arg) return 1;  
    if( sscanf(arg, "%s to %s", objectname, acceptor)==2 ){ 
        if(acceptor!="花白凤"&&acceptor!="hua baifeng"&&acceptor!="hua")
                return 1;
        if(obj->query("busy"))
        	return notify_fail("花白凤正在和别人说话，你稍等一下吧。\n");
        ob=present(objectname,me);
        if(!objectp(ob)) return 1;
if(!ob->query("changed"))
	return notify_fail("这东西花白凤是看不上的。\n");
	if (!ob->query("weapon_prop"))
			return notify_fail("花白凤只能帮你诅咒武器。\n");
			  if( ob->query("equipped") )
      return notify_fail("你必须放下这样东西才能进行诅咒。\n");
      
      if (!me->query("wanma/结局_ma"))
      	      return notify_fail("只有魔教传人才可以进行诅咒。\n");
      	      i = me->query("for_practice_modao");
      	      if (i<3) i =3;
  message_vision(HIC"\n咒语迷雾般缠绕着整个空间。。。\n"NOR, me);
     message_vision(HIC"\n咒语迷雾般缠绕着$N的" + ob->name() + HIC"上，一瞬间，让人恍然大悟。。。 \n"NOR,
                                me);
                message_vision(HIC"整个空间的黑暗似乎都集中在" + ob->name() + HIC"上，但一下子就把世间的黑暗全部带来，那么的阴冷，恐惧。。。\n"NOR, me);
            ob->set("for_modao",i);
            ob->save();
			} 
			return 1;
}