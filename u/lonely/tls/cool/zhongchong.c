#include <ansi.h>
#include <room.h>
inherit ROOM;
string look_left(object me);
string look_right(object me);
void create()
{
         set("short",HIY"中冲"NOR);
         set("long","这个山洞内一尘不染，非常干净，光线来自洞顶，似乎有块非常大的宝石，
   迎面墙壁上挂着两张图谱(tupu)，地上放着几个蒲团，你随便找了个地方坐了下来。\n"
);

          set("item_desc", ([
             "tupu" : "墙上挂着两张图谱(left)(right)，似乎就是六脉神剑的武功要诣。\n",
             "left": (: look_left :),
             "right": (: look_right :),
]));

        
set("exits", ([
               "southwest" : __DIR__"pyd",
        ]));
       
setup();
}
string look_left(object me)
{
       return YEL"\n这张图谱是一个卷轴舒开，帛面年深日久，已成焦黄之色，图上开头写着： \n"+
       "“六脉神剑”以一阳指指力为根基，将一阳指的指力化作剑气，有质无形，可称无形气剑。所谓六脉，\n"+
       "即手之六脉太阴肺经、厥阴心包经、少阴心经、太阳小肠经、阳明胃经、少阳三焦经,六脉神剑，即\n"+
       "是由六脉劲气化出的六种无形剑气。。。紧跟着帛上绘着个裸体男子的图形，身上注明穴位，以红线\n"+
       "黑线绘着内力的运走径道，旁边注着一行小字“中冲剑运气法门”。\n" NOR;
}
string look_right(object me)
{
        return YEL"\n这张图谱是一个卷轴舒开，帛面年深日久，已成焦黄之色，图上都是纵横交叉的直线、\n"+
        "圆圈和弧形,但见红线黑线，纵横交错，头绪纷繁之极，这图便是中冲剑的剑法，大开大阖，气势雄迈，\n"+
        "一招一势之间凌厉无比。\n" NOR;
}
void init()
{
        add_action("do_study", "yanxi");
        add_action("do_study", "xuexi");
        add_action("do_study", "xiulian");    
}

int do_study(string arg)
{
       object me,weapon;
       string *skill;
       int j,lvl,neili;
       mapping skill_name;
       me=this_player();
       
       neili=me->query("max_neili");
       skill_name=me->query("liumai-shenjian");
       lvl=me->query_skill("liumai-shenjian",1);
       if (skill_name)
       skill=keys(skill_name);
       j=sizeof(skill);
       
       weapon = me->query_temp("weapon");
      
       if(me->is_busy()|| me->is_fighting()) return notify_fail("你正忙着呢！\n");
       if (!arg) return 0;   
     
       if (weapon )
            return notify_fail("你手中拿着东西，怎么练？\n");   
    
       
       if(arg=="left" ) {
       	
       if (j>2) return notify_fail("你已经竭尽全力去体会图谱上的精要，可是总感觉体内数道内劲无法运转自如！\n");	
       if (lvl>30*(j+1)) me->set_skill("liumai-shenjian",30*(j+1));         
      
       if (neili<(j+1)*3000+1500&&!me->query("liumai-shenjian/zhongchong"))
            return notify_fail("你竭尽全力的驱动体内的一阳指真气，试图由中冲穴射出无形剑气，却无半点劲气发出。\n");

       
       if (lvl>30*(j+1))
            return notify_fail("你已经竭尽全力去体会图谱上的精要，可是总感觉内劲无法运气成束！\n");

       if (me->query("neili",1)<50)
            return notify_fail("你的内力快不够了！\n");   
       if (me->query("jing",1)<50)
            return notify_fail("你的精神快不够了！\n");         
       me->receive_damage("jing",40+random(10));
       me->receive_damage("neili",40+random(10));
if (lvl>=30*(j+1)||me->query("liumai-shenjian/zhongchong",1)){
       write("你内力运转自如，凝聚真气，中指迎空一划，嗤嗤声响，一条无形剑气自“中冲”穴中激射而出。\n");
       if (!me->query("liumai-shenjian/zhongchong"))
       me->add("liumai-shenjian/zhongchong", 1);
       } else {
       write("你照着图谱研习中冲剑法的运气法门，渐渐的悟出其中的精要所在。\n");
       if (!me->query("liumai-shenjian/zhongchong"))
       me->improve_skill("liumai-shenjian", me->query("int"));
       }
       return 1;
  }else if (arg=="right") {
  	
       if (!me->query("liumai-shenjian/zhongchong"))
            return notify_fail("你已经竭尽全力去体会图谱上的剑法，可惜这一路剑法的剑气你还没有练成！\n");
       if (me->query("neili",1)<60)
            return notify_fail("你的内力快不够了！\n");   
       if (me->query("jing",1)<60)
            return notify_fail("你的精神快不够了！\n");
       me->receive_damage("jing",50+random(10));
       me->receive_damage("neili",50+random(10));
       write("你照着剑谱研习中冲剑法，渐渐的悟出其中的精要所在。\n");
       me->add_temp("zhongchong", 1);
       if (me->query_temp("zhongchong")>=10) {
       me->add("liumai-shenjian/zhongchong", 1);
       me->set_temp("zhongchong",0);
       write("你凝聚真气，中指点处，将图上的中冲剑法演练了一遍。\n");
       }
      return 1;
	}     
 }   
int valid_leave(object me, string dir)
{
       me->set_temp("zhongchong", 0);
       return 1;        
}                    