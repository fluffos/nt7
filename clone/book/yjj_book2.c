//rama@sz
//易筋经残篇

inherit BOOK;

int do_xiulian();
int finish(object me);

void setup()
{}
void init()
{
        add_action("do_xiulian", "xiulian");
        add_action("do_xiulian", "xiu");
}

void create()
{
        set_name("易筋经残篇", ({ "yijinjing" }));
        set_weight(600);
              set("no_drop",1);
              set("no_get",1);
              set("no_steal",1);
        /*if (clonep())
        set_default_object(__FILE__);
        else*/
        {
                set("unit", "本");
                set("long", "这是一本梵文经书，每一页上都写弯弯曲曲的文字，没一个识得。\n");
                set("value", 5000);
                set("material", "paper");
                
        }
}

int do_xiulian()
{
        object me,ob;
        object where_1;
        int poison_lvl;
        me=this_player();
        if(!me->query_skill("poison",1))
        return notify_fail("你连基本的毒功都不会，还想领略这么高深的技巧？\n");
         
        poison_lvl = me->query_skill("poison",1);
               
        where_1 = environment(me);

        if (!present("yijinjing", me))
                return 0;
                
        if( me->is_busy() )
             return notify_fail("你正忙着呢！\n");       
        if( query("pigging", where_1) )
                return notify_fail("你还是专心拱猪吧！\n");

        if( query("sleep_room", where_1) )
                return notify_fail("不能在睡房里修炼，这会影响他人。\n");

        if( query("no_fight", where_1) )
                return notify_fail("这里空气不好，还是找别处吧！\n");

        if( query("name", where_1) == "大车里" )
                return notify_fail("车里太颠簸, 修练会走火入魔. \n");

        if( me->is_busy() || query_temp("pending/exercising", me) )
        if( me->is_fighting() )
                return notify_fail("战斗中不能修炼，会走火入魔。\n");

        if( query_temp("is_riding", me) )
                return notify_fail("在坐骑上修练，会走火入魔。\n");

        if( query("canewhua", me) == 1 )
                return notify_fail("你无法再从这本书上学到任何新东西了。\n");

        if( !stringp(me->query_skill_mapped("force")) || me->query_skill_mapped("force") != "huagong-dafa")
                return notify_fail("你必须先用 enable 化功大法。\n");

        if (poison_lvl < 250) 
                return notify_fail("第一页上面的一些用毒技巧，你怎么也领略不了，看来你的毒功还有待加强。");
        
        if(present("yijinjing",me) && !present("shenmuwang ding",me))
        {
                write("你开始按照定春秋教你的独特练功方法调息打坐。\n");
                if(random(4)==1){
                        write("没有神木王鼎的帮助，你根本无法控制住自己的气，你只觉得体内横冲直撞，你有些神智不清了！\n");
                        write("你哇的吐出一口鲜血，你只觉得意识在慢慢的消失！\n");
                        set_temp("die_reason", "修炼易筋经残扁，走火入魔死了", me);
                        me->receive_damage("qi",query("eff_qi", me)+200);
                        return 1;
                }
                else
                me->start_busy(30);
                call_out("finish",60);
                return 1;
        }

        ob=present("shenmuwang ding",me);
        if( query("fake", ob) || query("item_make", ob) )
        {
                return notify_fail("你试了半天，神木王鼎没有半点动静，看来是个假货！\n");
        }

        write("你开始按照易筋经上面独特的练功方法开始调息打坐。\n");
        write("神木王鼎也冒出了袅袅的清烟，一切都让你你觉得和谐极了，慢慢的甚至忘记了自我的存在。\n");
        if( random((200/query("int", me)))>3 )
        {
                write("忽然你觉得脑子里面有些混乱，好象哪个地方不对了！\n");
                write("你哇的吐出一口鲜血，你只觉得意识在慢慢的消失！\n");
                me->receive_damage("jing",30);
                me->receive_damage("qi",100);
                me->start_busy(30);
                return 1;
        }
        else
        {
                 me->start_busy(30);
                call_out("finish",60);
        }
        return 1;
}

int finish(object me)
{
        me=this_player();
        write("你只觉得浑身上下舒畅无比，不由暗自叹道：“真不愧是易筋经！”\n");
        me->clear_condition("bingcan_poison",5);
        if( query("yijinjing", me)<1 )
        {
                set("yijinjing", 1, me);
        }
        addn("yijinjing", 1, me);
        if( query("yijinjing", me) >= 10 )
        {
                write("你心台忽然一片明朗，多日来的疑虑一扫而空！你领悟出了化功大法真正精髓的所在！\n");
                delete("yijinjing", me);
                set("canewhua", 1, me);
                set("huagong_hua", 1, me);
                me->clear_condition("bingcan_poison");
                return 1;
                //学会yun hua
         }
         return 1;
}
