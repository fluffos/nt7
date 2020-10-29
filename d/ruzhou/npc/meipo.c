// NPC: /d/ruzhou/npc/meipo.c 只处理结婚与拜堂
// llm 99/06/04 修改

#include <ansi.h>

inherit NPC;
//inherit F_CLEAN_UP;

int do_marry(string arg);
int waiting(object ob);
int do_name(string target);
int do_chase(object ob);
int do_ok(object ob);
int meipo_waiting(object ob,object me,object obj);
int ready_marry(object ob,object me,object obj);
int wait_marry(object ob,object me,object obj);
int start_marry(object ob,object me,object obj);
int do_back(object ob);
int do_bai(string arg);

void create()
{
        set_name("媒婆", ({ "meipo","po" }) );
        set("title", HIM""NOR);
        set("gender", "女性" );
        set("age", 43);
        set("long",
                "一位精明能干的老媒婆。\n");
        set("combat_exp", 100000);
        set("attitude", "friendly");
        set("inquiry", ([
                "结婚" : "媒婆笑眯眯地点头道：“是啊... 要结婚(marry)当然要找我来做媒的呀！”\n",
                "marry" : "媒婆笑眯眯地点头道：“是啊... 要结婚(marry)当然要找我来做媒的呀！”\n",
      "登记" : "媒婆笑眯眯地点头道：“是啊... 要结婚(marry)登记当然要找我来做媒的呀！”\n",
                "离婚" : "媒婆脸色一变，有点勉强地笑道：“要...离婚(unmarry)？唉...！我可是看你们成婚的呀！\n"
              "不过你们要是一定要离的话，那得去汝州知府处办理了！”\n",
                "unmarry" : "媒婆脸色一变，有点勉强地笑道：“要...离婚(unmarry)？唉...！媒都是我作\n"
              "的，只好由我办，真是作啊！”\n",
      "费用":"媒婆嘻嘻笑道：“结婚这么大的事，花费的地方可不少，要50 gold，,而离婚\n"
              "更要花费不少钱，所以要100 gold。”\n",
        ]) );
        set_skill("literate", 100);
        set_skill("dodge", 500);
        set_skill("unarmed", 300);
   setup();
        add_money("gold", 4);
        carry_object("/clone/misc/cloth")->wear();
}

void init()
{
        object ob;
        ::init();
        add_action("do_marry", "marry");
   add_action("do_bai","拜");
        add_action("do_name","请");
}

int accept_object(object me, object ob)//交钱
{
   if( !query("money_id", ob) )
             return notify_fail("媒婆嘻嘻笑道：“我老婆子有吃有喝不收什么礼，您还是拿回去吧！”\n");
        if( !query_temp("ask_money", me))//由下面判断交钱的人是否符合结婚条件。
           return notify_fail("媒婆迷惑地问：“你想干什么？白给我钱？”\n");
          if(ob->value() < 500000)
              return notify_fail("媒婆皱了皱眉头说道：“钱太少了吧？50 gold，结婚这么大的事，再少就不行了。”\n");
        message_vision("媒婆接过钱对$N说：“这位"+RANK_D->query_respect(me)+"我可没赚你的钱，呆会儿我还要张罗喜堂、还\n"
                   "要雇人、还有办酒宴，搞不好我还得赔上一点的！而且我还可以帮你发请束，\n"
         "你可以输入‘请 <某人的中名>’。”\n",me);
        set_temp("marry/money", me->name(), this_object());//记录给过钱的人
          return 1;
}

int do_name(string target)//请客人
{
        object me,ob,dest, *all;
        int i;
        me = this_player();
        ob = this_object();
        all = users();

        if (me->is_busy())
                return notify_fail("媒婆说道：“你忙完后再和我说话吧！”\n");
        if( ob->is_fighting()||me->is_fighting() )
                return notify_fail("媒婆说道：“现在没功夫！”\n");
        if( !living(ob) )
                return notify_fail("你还是先想办法把媒婆救醒吧。\n");
        if( query_temp("marry/money", ob) != me->name() )
      return notify_fail("媒婆斜了斜你：“你又没交钱！”\n");
        if( query("waiting_target", ob) )
                return notify_fail("媒婆笑笑说：“不要急，我的小喜鹊们还没有飞回来呢！”\n");
        if( !target || target==" ")
                return notify_fail("媒婆抽出一张请柬写了几笔问：“你想请谁来参加你的婚礼？告诉我他(她)的名字！”\n");
        for(i=0; i<sizeof(all); i++)
        {
                if( target == all[i]->name() || target == query("id", all[i]) )
                        dest = all[i];
        }
        if( !dest )
                return notify_fail("媒婆告诉你：“很遗憾，您想请的人他现在不在游戏中！”\n");
        if (dest->is_ghost())
           return notify_fail("媒婆婉惜地地告诉你：“据我们所知，您要请的人已经死了，您请节哀顺便！”\n");
        set("waiting_target",query("id",  dest), ob);
        set("me_name",query("name",  me), ob);
        set("me_id",query("id",  me), ob);
        message_vision(HIG"媒婆一张喜柬上写上几个字，双手一拍，从东廊就飞出一只小喜鹊，衔着喜帖，\n"
   "扑愣愣地一下子消失在天空中了。\n" NOR,me);
        call_out("do_chase", 1, ob);
        return 1;
}

int do_chase(object ob)//喜鹊送请柬
{
        object dest,obj;
        dest=find_player(query("waiting_target", ob));

        if( !objectp(dest) || !environment(dest) )
        {
                call_out("waiting", 0, ob);
                return 1;
        }
        message_vision(HIY"天空中突然飞过来一只花喜鹊，落在$N肩头，将衔着的一张喜柬递给$N。\n" NOR, dest);
        obj = new(__DIR__"obj/xitie");
        set("name", HIR+query("me_name", ob)+"("+query("me_id", ob)+")"+"的结婚请帖"NOR, obj);
        obj->move(dest);
        call_out("do_ok", 0, ob);
        return 1;
}

int waiting(object ob)//喜鹊等待
{
        object dest;
        dest=find_player(query("waiting_target", ob));

        if ( objectp(dest)&&dest->is_ghost() )
        {
                        delete("waiting_target", ob);
                        call_out("do_ok", 1, ob);
                        return 1;
        }
        remove_call_out("waiting");
        call_out("waiting", 60, ob);
   return 1;
}

int do_ok(object ob)//喜鹊送柬成功回来
{
        message("vision", "突然看见花喜鹊从窗外飞进来，落在媒婆身旁，媒婆笑眯眯地抚着花喜鹊的头后\n"
                "说道：“请柬刚才已经都送到了！您还想请谁？不想请了就开始结婚手续(marry sb.)吧！”\n", environment(), ob);
          delete("waiting_target", ob);
        delete("me_name", ob);
        delete("me_id", ob);
        return 1;
}

int do_marry(string arg) //判断结婚
{
        object obj, me,ob,old_target;
        me = this_player();
        ob = this_object();
        if( query("gender", me) == "无性" )
                return notify_fail("媒婆哼了一声：“你无根无性，结个什么婚？！”\n");

        if( (query("age", me)<18) && (query("gender", me) == "男性" )
                 || (query("age", me)<16) && (query("gender", me) == "女性") )
                return notify_fail("媒婆笑嘻嘻地说道：“你们现在还年轻，以后再说吧！”\n");
        if (me->is_busy())
                return notify_fail("媒婆说道：“你现在不是正忙着吗？”\n");

        if( me->is_fighting(this_object()) )
        {
                if( !this_object()->is_killing(me) )
                        this_object()->kill_ob(me);
                return notify_fail("媒婆说道：“好，好，老娘送你去阴间成婚！”\n");
        }

        if( this_object()->is_fighting() )
                return notify_fail("媒婆说道：“没看见这儿有人捣乱吗！“\n");

        if( !living(this_object()) )
                return notify_fail("你还是先想办法把媒婆救醒吧。\n");

        if( me->is_fighting() )
                return notify_fail("媒婆说道：嘿嘿，你先还是料理完你的朋友再说吧！\n");

        if( !environment() || base_name(environment()) != query("startroom"))
                return notify_fail("媒婆说道：“真抱歉，我现在很忙，请您等一会到红娘庄来找我吧。”\n");

        if( query("class", me) == "bonze" || query("jobname", me) == "bonze" )
                return notify_fail("媒婆笑道：“哈哈！怎么，信佛的也想开色戒了吗?”\n");

        if( query("jobname", me) == "taoist" )
                return notify_fail("媒婆摇了摇头道：“你修了道竟还是凡心不泯，唉！你要是真想，还是还了俗再来吧！”\n");

        if(!arg ||!find_player(arg) )
                return notify_fail("媒婆问道：“你想和谁喜结良缘？”\n");

        if(!objectp(obj = present(arg, environment(me))))
                return notify_fail("媒婆说道：“结婚可是要两个人一起来的呀！”\n");

        if( query_temp("pending/pro", me) )
                return notify_fail("媒婆奇道：“咦？你的婚礼不是正在进行中吗？还要问什么？”\n");

        if( query_temp("pending/pro", obj) )
                return notify_fail("媒婆说道：“你想给别人搅局吗？”\n");

        if( !obj->is_character() )
                return notify_fail("媒婆说道：“你这不是拿自己开涮吗。”\n");

        if( query("class", obj) == "bonze" || query("jobname", me) == "taoist" )
                return notify_fail("媒婆笑道：哈哈！"+ obj->name() +"可是出家人，别跟人家开玩笑了。\n");

        if( mapp(query("couple", me)) )
        {
      if( query("couple/married", me)>2 )
              return notify_fail("媒婆翻了翻姻缘簿，板下脸说道：“我早就跟你说过，怎么又来了？\n"
              "这次我实在不能帮你什么了，你结婚次数太多了，按朝廷纲纪，是不\n"
              "准再办理结婚手续了，你们去做对野鸳鸯吧！\n");
              if( query("couple/have_couple", me) )
              {
                      if( obj == present(query("couple/couple_id", me),environment(me)) )
                              return notify_fail("媒婆奇道：“你们本来就是夫妻呀！干嘛还要再来？”\n");
                      if( query("gender", me) == "女性" )
                              return notify_fail("媒婆说道：“你已经是有夫之妇了，这里不允许重婚的。”\n");
                      else
                              return notify_fail("媒婆说道：“你已经是有妇之夫了，这里不允许重婚的。”\n");
              }
        }
        if( mapp(query("couple", obj)) )
        {
      if( query("couple/married", obj)>2 )
              return notify_fail("媒婆翻了翻姻缘簿，叹了口气道：“早跟你们说过，怎么又离了，这\n"
           "次我实在不能帮你们什么了，你是没问题，但"+obj->name()+"结婚次数太多了，\n"
        "按朝廷纲纪，是不准再办理结婚手续了，你们去做对野鸳鸯吧！\n");
        if( query("couple/have_couple", obj) )
                {
                        if( query("gender", obj) == "女性" )
                                return notify_fail("媒婆说道：可惜她已经是有夫之妇了，这里不允许重婚的。\n");
                        else
                                return notify_fail("媒婆说道：可惜他已经是有妇之夫了，这里不允许重婚的。\n");
                }
        }
        if( !living(obj) )
                return notify_fail("媒婆摇摇头说道：“"+ obj->name()+"现在还没清醒过来，我还不能确定你们双方都是自愿的。”\n");

        if( query("gender", obj) == query("gender", me) )
                return notify_fail("媒婆惊道：“哇！你是同性恋？对不起，老婆子处理不了这事！”\n");

        if(obj == me)
                return notify_fail("媒婆说道：“你这不是拿自己开涮吗？”\n");

       if( !userp(obj) )
                return notify_fail("媒婆说道：“对不起，你只能和玩家结婚。”\n");

   if( query_temp("marry/money", ob) != me->name( )
            && query_temp("marry/money", ob) != obj->name())//只要其中有一个人给过就行
        {
           set_temp("ask_money", 1, me);
       set_temp("ask_money", 1, obj);//防止条件不符白结婚
           return notify_fail("媒婆笑嘻嘻地道：结婚总要花一笔钱的喽！要50 gold，不给钱，我可没法给你办！\n");
   }

        if( query("unmarried", me)>2 )
        {
           delete("unmarried", me);
      delete("married", me);
      set("couple/married", 2, me);
      message_vision("媒婆翻了翻姻缘簿，对$N说道：“婚姻大事怎么会象你这样随随便便？现在\n"
      "再给你最后一次机会，再离婚，我这儿就不给你办结婚了！”\n",me);
   }
        if( query("unmarried", obj)>2 )
   {
           delete("unmarried", obj);
      delete("married", obj);
      set("couple/married", 2, obj);
      message_vision("媒婆翻了翻姻缘簿，对$N说道：“婚姻大事怎么会象你这样随随便便？现在\n"
      "再给你最后一次机会，再离婚，我这儿就不给你办结婚了！”\n",obj);
   }
        if( !query_temp("marry/answer", me) )
   {
           message_vision(HIG"媒婆摊开姻缘簿，絮絮叨叨地说道：“结婚是一辈子的终身大事，可不能\n"
           "随随便便，否则，这世道就乱了。每个人只能在我这里办三次结婚手续。\n"
           "让我看看："HIC""+me->name()+"结过"+query("couple/married", me)+"次婚；"+obj->name()+"结过"+query("couple/married", obj)+"次婚；"
           HIG"好的，\n最后，你们再认真考虑一下：是不是真心愿意和对方结婚？”\n"NOR,me);
           set_temp("marry/answer", 1, obj);
   }
        if( query_temp("pending/marry", obj) != me )
        {
                if( query("gender", obj) == "女性" )
                        message_vision(MAG "\n$N对著$n问道：“你愿意嫁给我吗？”\n\n"NOR, me,obj);
                else
                        message_vision(MAG "\n$N对著$n问道：“你愿意娶我吗？”\n\n"NOR, me,obj);

                if( objectp(old_target=query_temp("pending/marry", me)) && old_target != obj )
                        tell_object(old_target, YEL + me->name() +
                        "取消了和你结婚的念头。\n" NOR);

                set_temp("pending/marry", obj, me);

                if( query("gender", obj) == "女性" )
                        tell_object(obj, MAG "如果你愿意嫁给他，请你也对" + me->name()
                        +"("+query("id", me)+")"+"下一次marry指令。\n"NOR);
                else
                        tell_object(obj, MAG "如果你愿意娶她，请你也对" + me->name() +
                        "("+query("id", me)+")"+"下一次marry"+query("id", me)+"的指令。\n"NOR);
      write(MAG"现在你急切盼望着你的心上人说同意...\n" NOR);
      return 1;
        }
        message_vision(MAG "\n$N对著$n大声说道：我愿意！\n\n"NOR, me,obj);
        message_vision(MAG "媒婆呵呵笑道：“那就好，那就好，都跟我到东边的姻缘堂来准备拜堂吧！”\n"
           "说完，媒婆一扭一扭地走进了东边的大堂。\n" NOR, obj, me);
        delete_temp("ask/marry", me);
        ob->move("/d/ruzhou/yinyuan-tang");

        set_temp("pending/pro", 1, me);
        set_temp("pending/pro", 1, obj);

        set("couple/couple_name", obj->name(), me);
        set("couple/couple_id",query("id",  obj), me);

        set("couple/couple_name", me->name(), obj);
        set("couple/couple_id",query("id",  me), obj);

        if( query("gender", obj) == "女性" )
        {
                set("couple/couple_gender", "妻子", me);
                set("couple/couple_gender", "丈夫", obj);
        }
        else
        {
                set("couple/couple_gender", "妻子", obj);
                set("couple/couple_gender", "丈夫", me);
        }
   call_out("meipo_waiting", 1,ob,me,obj);
         return 1;
}

int meipo_waiting(object ob,object me,object obj)//媒婆等拜堂
{
        if( query_temp("wait_time", ob) == 200 )
        {
                say( "媒婆疑惑地说道：“小夫妻连拜堂也不急？难道真是有缘无份？唉，婚礼还是取消罢！\n"
              "老娘可是白赚了50 gold了，呵呵呵...”\n\n");
                call_out("do_back", 0, ob);
      return 1;
        }
        if( environment(ob)==environment(me)&&environment(ob)==environment(obj) )
   {                                                 //两人都在
      delete_temp("wait_time", ob);
           call_out("ready_marry", 1,ob,me,obj);
   }
        else
   {
                if( environment(ob)==environment(me)&&environment(ob)!=environment(obj) )
                {
                        if( random(10) == 0 )
                        say("\n媒婆问道：“"+me->name()+"！你去问问"+obj->name()+"怎么还不过来？难道不愿意了？\n");
                        addn_temp("wait_time", 1, ob);//其中一人obj不在
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
           else if( environment(ob)!=environment(me)&&environment(ob)==environment(obj) )
                {                                            //其中一人me不在
                        if( random(10) == 0 )
                        say("\n媒婆问道：“"+obj->name()+"！你去问问"+me->name()+"怎么还不过来？难道不愿意了？\n");
                        addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob,me,obj);
                }
                else
      {
                   addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob,me,obj);
      }
   }
        return 1;
}

int ready_marry(object ob,object me,object obj)//准备婚礼
{
        object room,npc;

        if(!( room = find_object("/d/ruzhou/yinyuan-tang")) )
        room = load_object("/d/ruzhou/yinyuan-tang");

        message("vision", HIY "\n媒婆高声叫道：“快快快，干活的都出来了，马上布置喜堂！”\n" NOR, room);
        message("vision", HIC"\n只听堂后响起一阵脚步声，十几个穿得五彩鲜艳衣服的少男少女嘻嘻哈哈地跑进来，\n"
                "叽叽喳喳地议论着，又分头跑开了，时不时地笑着看一看"+me->name()+"和"+obj->name()+"。\n\n"NOR, room);
        say("媒婆对两位新人说道：“不要着急，我们都是很有经验的，很快就会布置好的！”\n"
   CYN"只见身边的人跑来跑去，忙得不得了。\n"NOR);
        call_out("wait_marry", 1, ob,me,obj);
   return 1;
}

int wait_marry(object ob,object me,object obj) //布置喜堂
{
        object room;
        if(!( room = find_object("/d/ruzhou/yinyuan-tang")) )
        room = load_object("/d/ruzhou/yinyuan-tang");
        switch(query_temp("wait_time", ob) )
        {
           case 0:
            say(RED"\n一个小家伙跑过来，叫道：“媒婆，买红纸的钱不够了！”媒婆赶紧给他一些钱。\n\n"NOR);
           set_temp("wait_time", 1, ob);
           call_out("wait_marry", 1, ob,me,obj);
           break;
      case 1:
             say(MAG"\n突然，那边的小姑娘叫道：“媒婆，红鸳鸯贴这边正不正？”媒婆一看：“右边再上去点！”\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
      case 2:
             say(CYN"\n四个家伙哼哟嘿哟地抬着一只大箱子从屋外你身边走过，媒婆叮嘱道：“慢些、轻点！”\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
                case 3:
      say("\n媒婆一把拉住身边跑过的一个小伙子：“迎宾楼的喜宴订了吗？快去！”\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
      case 4:
             say(YEL"\n那边的人叫道：“快拿火折来，把香烛点亮、点亮。”\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
           break;
                case 5:
             say("\n那边又叫起来：“媒婆，给点钱打发送货来的吧！”“来了！”媒婆赶紧跑过去。\n\n");
      addn_temp("wait_time", 1, ob);
                 call_out("wait_marry", 1, ob,me,obj);
      break;
                case 6:
             say(CYN"\n媒婆一路小跑过来，看看新郎新娘的身材，点点头回头叫：“快，给新人准备喜装。”\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
                case 7:
                  say(WHT"\n一帮人七手八脚地抬出了几张大椅子，在中堂上挂了一个大大的\n"HIR
"                               ■      ■\n"
"                            ■■■■■■■■\n"
"                            ■■■■■■■■\n"
"                             ■■■  ■■■\n"
"                             ■■■  ■■■\n"
"                              ◆◆    ◆◆\n"
"                            ■■■■■■■■\n"
"                             ■■■  ■■■\n"
"                             ■■■  ■■■\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
           case 8:
             say(YEL"\n唢呐乐手开始调试欢快的乐曲，进进出出不少认识不认识的人，纷纷拱手相贺：“恭喜恭喜！”\n\n"NOR);
      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
      break;
                case 9:
                    say("\n几个小姑娘笑嘻嘻地一边擦着桌椅，一边互相咬着耳朵，不时地偷眼看看新人。\n\n");
      message("vision", HIY "\n媒婆高声问了一声：“都准备好了吗？”众人应道：“好了！”\n"
      "媒婆立刻拖长了声音喊道：“有请月老主持婚礼……！”\n"
      YEL"顿时，鼓乐齐鸣，鞭炮大作，伴郎伴娘拥过来，七手八脚给新郎、新娘换上新衣，\n"
      "缀拥着向大堂中央走去。\n"NOR,room);
              addn_temp("wait_time", 1, ob);
              call_out("start_marry", 1, ob,me,obj);
//            call_out("wait_marry", 1, ob,me,obj);
                break;
//                case 10:
//      call_out("start_marry", 1, ob,me,obj);
//      break;
   }
   return 1;
}

int start_marry(object ob,object me,object obj) //开始婚礼
{
        object moon,room;
   string msg;
        if(!(room = find_object("/d/ruzhou/yinyuan-tang")))
                room = load_object("/d/ruzhou/yinyuan-tang");
        moon=new(__DIR__"yuelao");
   moon->move(room);
        message("vision", "\n随着一阵哈哈大笑，一位红面白须的老者，快步踱进堂中，在场的少年男女都躬身相拜：\n"
           "“恭请月老爷爷！”月老摆摆手，笑呵呵地看看"+me->name()+"和"+obj->name()+"，点点头道：\n"
      "“好！好！郎才女貌，天作之合！天作之合呀！”\n"
           HIY"\n媒婆一挥手，喜乐又高起，只听见月老高声宣布：“新郎…新娘…拜…天地……！”\n"NOR,room, moon);
   say("媒婆又小声地对两个新人说：“按顺序输入‘拜 天地、拜 高堂和拜 对方的名字’。”\n");
   CHANNEL_D->do_channel(moon, "mudnews",
           sprintf("恭贺%s和%s喜结良缘，拜堂大礼即时开始！\n",me->name(),obj->name()));
        set_temp("pending/bai", 1, me);
   set_temp("pending/bai", 1, obj);
        return 1;
}

int do_back(object ob)//结束
{
   delete_temp("wait_time", ob);
   delete_temp("marry/money", ob);
        say("媒婆拍了拍身上，又一扭一扭地向西边走去。\n");
   ob->move("/d/ruzhou/hongniang-zhuang");
        return 1;
}

int do_bai(string arg)//拜堂
{
        object me,ob,obj;
        string act;

        me = this_player();
   ob = this_object();
        if (me->is_busy())
                return notify_fail("媒婆说道：“你现在不是正忙着吗？忙完再说！”\n");

        if( me->is_fighting(this_object()) )
        {
                if( !this_object()->is_killing(me) )
                        this_object()->kill_ob(me);
                return notify_fail("媒婆说道：“老娘好心给你办婚事，你敢动武，送你去阴间成婚吧！”\n");
        }

        if( this_object()->is_fighting() )
                return notify_fail("媒婆说道：没看见这儿有人捣乱吗！\n");

        if( !living(this_object()) )
                return notify_fail("你还是先想办法把媒婆救醒吧。\n");

        if( me->is_fighting() )
                return notify_fail("媒婆说道：“嘿嘿，你先还是料理完你的朋友再说吧！”\n");

        if( !environment()||base_name(environment()) != ("/d/ruzhou/yinyuan-tang") )
                return notify_fail("媒婆说道：“你这人真是的，拜堂是要到姻缘堂才行的呀！”\n");

        if( !query_temp("pending/bai", me) )
                return notify_fail("媒婆笑道：“哈哈，你犯什么傻呀！”\n");

        if( !objectp(obj=present(query("couple/couple_id", me),environment(me)) )
                 || !find_player(query("couple/couple_id", me)) )
        {
           message_vision("媒婆转身一看，惊讶地说道：“唉呀！你的爱人怎么突然跑了？婚礼怎么举行？大伙散摊吧。”\n"
              "在一片惋惜声，大家纷纷离场，喜堂上的东西也是一收而空。\n",me);
      call_out("do_back",1,ob);
      return 1;
   }

   if( arg == "天地" || arg == "高堂" || arg == ""+query("couple/couple_name", me) )
                return notify_fail("“拜”与后面的词之间请用半角空格。\n");

        if( !arg || (query_temp("pending/bai", me) == 1 && arg != "天地" )
                 || (query_temp("pending/bai", me) == 2 && arg != "高堂" )
                 || (query_temp("pending/bai", me) == 3 && arg != query("couple/couple_name", me)) )
                return notify_fail("媒婆笑道：“你乱拜什么呀？一拜天地！二拜高堂！三拜你的爱人！可别再错了！”\n");

        if( query_temp("pending/act", obj) != arg )
        {
      if( query_temp("pending/bai", me) != 3 )
      {
                        tell_object(obj, MAG"你的伴侣正等着和你拜 " + arg + " 呢...\n" NOR);
                        write(MAG "现在你正等待着你的伴侣...\n" NOR);
                        set_temp("pending/act", arg, me);
      }
      else
      {
                        tell_object(obj, MAG"你的伴侣正等着和你互拜（拜他的名字）呢...\n" NOR);
                        write(MAG "现在你正等待着你的伴侣...\n" NOR);
                        set_temp("pending/act", me->name(), me);
      }
                return 1;
        }
        else if( query_temp("pending/bai", me) == 1 )
   {
                  message_vision("“一拜…天…地……”$N和$n在阵阵鼓乐声中盈盈拜下......\n",me,obj);
      addn_temp("pending/bai", 1, me);
      addn_temp("pending/bai", 1, obj);
      return 1;
   }
        else if( query_temp("pending/bai", me) == 2 )
   {
                  message_vision("“二拜…高…堂……”$N和$n在站起来相视一笑，又缓缓拜下......\n",me,obj);
      addn_temp("pending/bai", 1, me);
      addn_temp("pending/bai", 1, obj);
      return 1;
   }
        else if( query_temp("pending/bai", me) == 3 )
   {
                  message_vision("“夫妻…对…拜……”$N和$n在相互深深拜了一拜......\n",me,obj);
                message_vision(HIY "月老笑呵呵地说道：“好，$N和$n，现在正式结为夫妻! \n" NOR, obj, me);
                CHANNEL_D->do_channel(this_object(), "chat",
                        sprintf( "恭喜%s和%s，一对璧人喜结良缘。\n        各位亲朋好友，可携礼到汝州迎宾楼参加他们的婚宴！\n", me->name(), obj->name()));

                addn("couple/married", 1, me);//结婚次数
                set("couple/have_couple", 1, me);//处于已婚状态
      set_temp("married_party", 1, me);//做上记号，喜来福老板看到就会同意开酒席
      set_temp("married_party", 1, obj);//两人都做，但只有男性才有用
                addn("couple/married", 1, obj);//结婚次数
                set("couple/have_couple", 1, obj);//已婚状态

      delete_temp("pending/bai", me);
      delete_temp("pending/bai", obj);
      delete_temp("pending/act", me);
      delete_temp("pending/act", obj);
                delete_temp("pending/pro", me);
                delete_temp("pending/pro", obj);
             delete_temp("ask_money", me);
           delete_temp("ask_money", obj);
           call_out("last_marry",1,ob,me,obj);
                return 1;
   }
}

int last_marry(object ob,object me,object obj)//拜堂结束
{
        object moon,room;
        if(!(room = find_object("/d/ruzhou/yinyuan-tang")))
                room = load_object("/d/ruzhou/yinyuan-tang");
        moon = present("yue lao", room);
        moon->move("/d/city/empty");
   delete_temp("wait_time", ob);
   delete_temp("marry/money", ob);
        say("媒婆喊道：“轿夫！快将新人送到迎宾楼举行婚宴，我和月老就不去了，呵呵！”\n说完一扭一扭地向西边走去。\n");
   ob->move("/d/ruzhou/hongniang-zhuang");
        message_vision(HIR"伴郎伴娘拥着两位新人，上了门口的两顶大红花轿，只听轿夫们一声“起轿！”\n"
           "一行人吹吹打打地奔向迎宾楼......\n"NOR,me,obj);
   me->move("/d/ruzhou/jiao1");
   obj->move("/d/ruzhou/jiao2");
   call_out("go_lou",8,ob,me,obj);
        return 1;
}

int go_lou(object ob,object me,object obj)//到酒楼
{
        object room,npc;
        if(!(room = find_object("/d/ruzhou/xifu-tang")))
                room = load_object("/d/ruzhou/xifu-tang");
        message_vision("\n    过了好长一会儿，只听轿夫们一声“到啦！”轿子整个儿一震，想是落到了地上，\n"
           "$N和$n从轿子中下来一看，原来已经到了迎宾楼。两人又被拥扶着一直上了二楼福满堂。\n"
      "只听到一阵呵呵笑声，迎宾楼老板喜来福笑容满面地迎出来：“恭喜两位新人！恭喜恭喜！\n”",me,obj);
   npc=new(__DIR__"xi-laifu");//老板出现
   set("name1", me->name(), npc);
   set("name2", obj->name(), npc);//双方姓名
   npc->move("/d/ruzhou/xifu-tang");
   me->move("/d/ruzhou/xifu-tang");
   obj->move("/d/ruzhou/xifu-tang");
   return 1;
}