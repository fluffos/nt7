#include <ansi.h>

private string *check_skill = ({ 
            "changquan",         
            "luohan-quan",
            "fuhu-quan",
            "mohe-zhi",
            "yizhi-chan",
});

private string *check_skilltemp = ({
            "cuff",
            "cuff",
            "cuff",
            "finger",
            "finger",
});

private string *check_skillname = ({
            "八震字决",
            "罗汉降魔",
            "罗汉伏虎",
            "摩诃参禅",
            "惊魔一指",
});


private string *check_canpfm = ({
            "can_perform/changauan/zhen",
            "can_perform/luohan-quan/xiangmo",
            "can_perform/fuhu-quan/fuhu",
            "can_perform/mohe-zhi/mohe",
            "can_perform/yizhi-chan/jingmo",

});

int do_ask();

int init()
{
        add_action("do_ask", "ask");
}

int do_ask(string arg) 
{ 
        int i;
        object me, ob; 
        string msg;
        
        me = this_player(); 
        ob = this_object();
          
        if( !arg || sscanf(arg, "%s", msg) != 1 ) 
        {
         message_vision(CYN "如果你要向我求教武功招式，直接(ask XXXX)就可以了!" NOR, ob, me);
         return 1); 
        }
          
        for(i=0; i< sizeof(check_skill); i++)
        {
           if (check_skillname[i] == msg)
           {
        
                 if( query(check_canpfm[i], me) )
                 {
                     message_vision(CYN "我不是已经教过你了吗？" NOR, ob, me); 
                     return 1; 
                 }

                 if( query("family/family_name", me) != query("family/family_name", ob) )
                 {
              
                     message_vision(CYN RANK_D->query_respect(me) + "和本派素无瓜葛，何出此言？" NOR, ob, me); 
                     return 1;
                  }

                 if (me->query_skill(check_skill[i], 1) < 1)
                 {
                     message_vision(CYN "你连" + to_chinese(check_skill[i]) + "都未曾学过，何来绝招？" NOR, ob, me);
                     return 1;
                 }
      
                 if( query("gongxian", me)<100 )
                 { 
                     message_vision(CYN "你虽在我少林门下，却甚无作为，这招我先不忙传你。" NOR, ob, me); 
                     return 1; 
                 }
        
                 if (me->query_skill("force") < 100)
                 {
                     message_vision(CYN "你的内功火候不足，学不成这招。" NOR, ob, me);          
                     return 1; 
                 }
        
                 if (me->query_skill(check_skill[i], 1) < 80)
                 {
                     message_vision(CYN "你的"+ to_chinese(check_skill[i]) + "火候未到，还得多练习练习。" NOR, ob, me);
                     return 1; 
                 }
       
                 message_vision(HIY "$n" HIY "点了点头，伸手将$N" HIY "招至" 
                                    "身边，在耳旁低声细说良久，$N" HIY "听" 
                                    "后会\n心的一笑，看来大有所悟。\n" NOR, me, ob); 
                                                                        
                 command("nod"); 
                 command("say 明白了？"); 
                 tell_object(me, HIC "你学会了「" + check_skillname[i] + "」。\n" NOR); 
      
                 if (me->can_improve_skill(check_skilltemp[i])) 
                     me->improve_skill(check_skilltemp[i], 1500000); 

                 if (me->can_improve_skill(check_skill[i])) 
                     me->improve_skill(check_skill[i], 1500000); 
                     me->improve_skill("martial-cognize", 1500000); 
                     set(check_canpfm[i], 1, me);
                     addn("gongxian", -100, me);
                 return 1; 
             }

         }

} 
