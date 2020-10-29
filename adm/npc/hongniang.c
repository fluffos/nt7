// llm 99/06/04 修改2000.09
// updated by lonely 11/03
// hongniang.c 红娘

#include <ansi.h>

#define MARRY_RING      "/clone/misc/wedding-ring.c"
#define RING_DIR        "/data/item/ring/"

inherit NPC;

int waiting(object ob);
int do_name(string target);
int do_chase(object ob);
int do_ok(object ob);
int meipo_waiting(object ob, object me, object obj);
int ready_marry(object ob, object me, object obj);
int wait_marry(object ob, object me, object obj);
int start_marry(object ob, object me, object obj);
int do_back(object ob);
int do_bai(string arg);
int ask_baitang();

void create()
{
        set_name("红娘", ({ "hong niang", "hongniang", "marriage witness" }));
        set("long", 
                "她是一个长得很好看的小姑娘，忽闪忽"
                "闪的大眼睛透着一丝狡黠。\n");
        set("gender", "女性");
        set("age", 18);
        set("str", 200);
        set("combat_exp", 1000);

        set("inquiry", ([
                "结婚": "要结婚？我可以为你们做媒啊，你们人都来齐了么？",
                "离婚": "结婚找我，离婚我也帮忙，不过可以慎重哦。一日夫妻百日恩嘛！",
                "拜堂": (: ask_baitang :),
        ]));

        setup();
        seteuid(getuid());
}

void init()
{
           add_action("do_bai", "拜");
        add_action("do_name", "请");
        add_action("do_name", "qing");
}

int accept_object(object me, object ob) 
{
           if( !query("money_id", ob) || !query("couple/id", me) || 
               !query_temp("ask_money", me) )
                     return notify_fail("红娘嘻嘻笑道：“我老婆子有吃有喝不收什么礼，您还是拿回去吧！”\n");

          if (ob->value() < 10000000)
                      return notify_fail("红娘皱了皱眉头说道：“钱太少了吧？1000 gold，如果是结婚这么大的事，再少就不行了。”\n");
              
        message_vision("红娘接过钱对$N说：“这位" + RANK_D->query_respect(me) + "我可没赚你的钱，呆会儿我还要张罗喜堂、还\n"
                          "要雇人、还有办酒宴，搞不好我还得赔上一点的！而且我还可以帮你发请束，\n"
                        "你可以输入‘请 <某人的中名>’。”\n", me);
        set_temp("marry/money", me->name(), this_object());
        command("say 你先告诉我你要请(qing)哪些人吧，如果不想请朋友，那么就准备拜堂(ask hong niang about 拜堂)吧！");
          return 1;
}

int do_name(string target)
{
        object me, ob, dest, *all;
        int i;
        me = this_player();
        ob = this_object();
        all = users();
                  
           if (query_temp("marry/money") != me->name())
           {
                   message_vision(name() + "笑嘻嘻地道：结婚总要花一笔钱的喽！" 
                                  "要 1000 gold，不给钱，我可没法给办！\n", me);
                   return 1;
           }
           
        if (me->is_busy())
                return notify_fail("红娘说道：“你忙完后再和我说话吧！”\n");
                
        if (ob->is_fighting() || me->is_fighting())
                return notify_fail("红娘说道：“现在没功夫！”\n");
                
        if (! living(ob))
                return notify_fail("你还是先想办法把红娘救醒吧。\n");
                
        if( query_temp("marry/money", ob) != me->name() )
                      return notify_fail("红娘斜了斜你：“你又没交钱！”\n");
                      
        if( query("waiting_target", ob) )
                return notify_fail("红娘笑笑说：“不要急，我的小喜鹊们还没有飞回来呢！”\n");
                
        if (! target || target == " ")
                return notify_fail("红娘抽出一张请柬写了几笔问：“你想请谁来参加你的婚礼？告诉我他(她)的名字！”\n");
                
        for (i = 0; i < sizeof(all); i++)
        {
                if( target == all[i]->name() || target == query("id", all[i]) )
                        dest = all[i];
        }
        
        if (! dest)
                return notify_fail("红娘告诉你：“很遗憾，您想请的人他现在不在游戏中！”\n");
                
        if (dest->is_ghost())
                   return notify_fail("红娘婉惜地地告诉你：“据我们所知，您要请的人已经死了，您请节哀顺便！”\n");
                   
        set("waiting_target",query("id",  dest), ob);
        set("me_name",query("name",  me), ob);
        set("me_id",query("id",  me), ob);
        message_vision(HIG "红娘一张喜柬上写上几个字，双手一拍，从东廊就飞出一只小喜鹊，衔着喜帖，\n"
                          "扑愣愣地一下子消失在天空中了。\n" NOR, me);
        call_out("do_chase", 1, ob);
        return 1;
}

int do_chase(object ob)
{
        object dest, obj;
        dest=find_player(query("waiting_target", ob));

        if (! objectp(dest) || ! environment(dest))
        {
                call_out("waiting", 0, ob);
                return 1;
        }
        
        message_vision(HIY "天空中突然飞过来一只花喜鹊，落在$N肩头，将衔着的一张喜柬递给$N。\n" NOR, dest);
        obj = new("/adm/npc/obj/xitie"); 
           set("name", HIR+query("me_name", ob)+"("+query("me_id", ob)+")"+"的结婚请帖"NOR, obj);
        obj->move(dest);
        call_out("do_ok", 0, ob);
        return 1;
}

int waiting(object ob)
{
        object dest;
        dest=find_player(query("waiting_target", ob));

        if (objectp(dest) && dest->is_ghost())
        {
                delete("waiting_target", ob);
                call_out("do_ok", 1, ob);
                return 1;
        }
        remove_call_out("waiting");
        call_out("waiting", 60, ob);
           return 1;
}

int do_ok(object ob)
{
        message("vision", "突然看见花喜鹊从窗外飞进来，落在红娘身旁，红娘笑眯眯地抚着花喜鹊的头后\n"
                "说道：“请柬刚才已经都送到了！您还想请谁？不想请了就开始结婚其他手续(ask hong niang about 拜堂)吧！”\n", 
                environment(), ob);
          delete("waiting_target", ob);
        delete("me_name", ob);
        delete("me_id", ob);
        return 1;
}

int ask_baitang()
{
        object me, obj, 
        
        ob = this_object();
        me = this_player();
        
           if (query_temp("marry/money") != me->name() || ! mapp(query("couple", me))) 
        {
                tell_object(me, "红娘迷惑不解的看着你！\n");
                return 1;
        }
                
        if( !(obj=present(query("couple/id", me),environment(me))) )
        {
                tell_object(me, "你的伴侣不在啊！\n");
                return 1;
        }
        
        message("vision", MAG "\n红娘呵呵笑道：“那就好，那就好，都跟我到东边的姻缘堂来准备拜堂吧！”\n"
                "说完，红娘一扭一扭地走进了东边的大堂。\n" NOR, me, obj);    
                   
           ob->move("/d/suzhou/yinyuan-tang");
        call_out("meipo_waiting", 1, ob, me, obj);
        return 1;
}

int meipo_waiting(object ob, object me, object obj) 
{
        if( query_temp("wait_time", ob) == 200 )
        {
                say("红娘疑惑地说道：“小夫妻连拜堂也不急？难道真是有缘无份？唉，婚礼还是取消罢！\n"
                          "老娘可是白赚了1000 gold了，呵呵呵...”\n\n");
                call_out("do_back", 0, ob);
                      return 1;
        }
        if (environment(ob) == environment(me) && environment(ob) == environment(obj))
           {                                                
                      delete_temp("wait_time", ob);
                   call_out("ready_marry", 1, ob, me, obj);
           }
        else
           {
                if (environment(ob) == environment(me) && environment(ob) != environment(obj))
                {
                        if (random(10) == 0)
                                say("\n红娘问道：“" + me->name() + "！你去问问" + obj->name() +
                                    "怎么还不过来？难道不愿意了？\n");
                        addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob, me, obj);
                }
                   else if (environment(ob) != environment(me) && environment(ob) == environment(obj))
                {                                            
                        if (random(10) == 0)
                                say("\n红娘问道：“" + obj->name() + "！你去问问" + me->name() +
                                    "怎么还不过来？难道不愿意了？\n");
                        addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob, me, obj);
                }
                else
                      {
                           addn_temp("wait_time", 1, ob);
                        call_out("meipo_waiting", 1, ob, me, obj);
                      }
           }
        return 1;
}

int ready_marry(object ob, object me, object obj)
{
        object room;

        if (! (room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");

        message("vision", HIY "\n红娘高声叫道：“快快快，干活的都出来了，马上布置喜堂！”\n" NOR, room);
        message("vision", HIC "\n只听堂后响起一阵脚步声，十几个穿得五彩鲜艳衣服的少男少女嘻嘻哈哈地跑进来，\n"
                "叽叽喳喳地议论着，又分头跑开了，时不时地笑着看一看" + me->name() + "和" + obj->name() + "。\n\n" NOR, 
                room);
        say("红娘对两位新人说道：“不要着急，我们都是很有经验的，很快就会布置好的！”\n"
               CYN "只见身边的人跑来跑去，忙得不得了。\n"NOR);
        call_out("wait_marry", 1, ob, me, obj);
           return 1;
}

int wait_marry(object ob, object me, object obj) 
{
        object room;
        object m_cloth, w_cloth;
        
        if (! (room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");
        
        switch(query_temp("wait_time", ob) )
        {
           case 0:
                    say(RED "\n一个小家伙跑过来，叫道：“红娘，买红纸的钱不够了！”红娘赶紧给他一些钱。\n\n" NOR);
                   set_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                   break;
              case 1:
                     say(MAG "\n突然，那边的小姑娘叫道：“红娘，红鸳鸯贴这边正不正？”红娘一看：“右边再上去点！”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
              case 2:
                     say(CYN "\n四个家伙哼哟嘿哟地抬着一只大箱子从屋外你身边走过，红娘叮嘱道：“慢些、轻点！”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
        case 3:
                      say("\n红娘一把拉住身边跑过的一个小伙子：“喜福堂的喜宴订了吗？快去！”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
              case 4:
                     say(YEL "\n那边的人叫道：“快拿火折来，把香烛点亮、点亮。”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                   break;
        case 5:
                     say("\n那边又叫起来：“红娘，给点钱打发送货来的吧！”“来了！”红娘赶紧跑过去。\n\n");
                      addn_temp("wait_time", 1, ob);
                 call_out("wait_marry", 1, ob, me, obj);
                      break;
        case 6:
                     say(CYN "\n红娘一路小跑过来，看看新郎新娘的身材，点点头回头叫：“快，给新人准备喜装。”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
        case 7:
                  say(WHT "\n一帮人七手八脚地抬出了几张大椅子，在中堂上挂了一个大大的\n" HIR
"                               ■      ■\n"
"                            ■■■■■■■■\n"
"                            ■■■■■■■■\n"
"                             ■■■  ■■■\n"
"                             ■■■  ■■■\n"
"                              ◆◆    ◆◆\n"
"                            ■■■■■■■■\n"
"                             ■■■  ■■■\n"
"                             ■■■  ■■■\n\n" NOR);
                addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
           case 8:
                     say(YEL "\n唢呐乐手开始调试欢快的乐曲，进进出出不少认识不认识的人，纷纷拱手相贺：“恭喜恭喜！”\n\n" NOR);
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                      break;
        case 9:
                    say("\n几个小姑娘笑嘻嘻地一边擦着桌椅，一边互相咬着耳朵，不时地偷眼看看新人。\n\n");
                      addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob, me, obj);
                break;
        case 10:
                    say("\n两位彩衣少女过来将一套大红金边滚龙袍递给新郎，一套青边戴花水云袖交给新娘道：“有请新郎新娘穿喜装”。\n\n");
                    m_cloth = new("/d/suzhou/npc/obj/longpao");
                    w_cloth = new("/d/suzhou/npc/obj/yunxiu");
                    if( query("gender", me) == "男性" )
                    {
                            m_cloth->move(me);
                            w_cloth->move(obj);
                    }
                    else
                    {
                            m_cloth->move(obj);
                            w_cloth->move(me);
                    }
                addn_temp("wait_time", 1, ob);
                  call_out("wait_marry", 1, ob,me,obj);
                break;                
        case 11:
                message("vision", HIY "\n红娘高声问了一声：“都准备好了吗？”众人应道：“好了！”\n"
                              "红娘立刻拖长了声音喊道：“有请月老主持婚礼……！”\n"
                              HIM "顿时，鼓乐齐鸣，鞭炮大作，伴郎伴娘拥过来，七手八脚给新郎、新娘换上新衣，\n"
                              "缀拥着向大堂中央走去。\n" NOR, room);
                      call_out("start_marry", 1, ob, me, obj);
                      break;
           }
           return 1;
}

int start_marry(object ob, object me, object obj) 
{
        object moon, room;

        if (! (room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");
        moon = new("/d/suzhou/npc/yuelao");
           moon->move(room);
        message("vision", "\n随着一阵哈哈大笑，一位红面白须的老者，快步踱进堂中，在场的少年男女都躬身相拜：\n"
                   "“恭请月老爷爷！”月老摆摆手，笑呵呵地看看" + me->name() + "和" + obj->name() + "，点点头道：\n"
                      "“好！好！郎才女貌，天作之合！天作之合呀！”\n"
                   HIY "\n红娘一挥手，喜乐又高起，只听见月老高声宣布：“新郎…新娘…拜…天地……！”\n" NOR, room, moon);
           say("红娘又小声地对两个新人说：“按顺序输入‘拜 天地、拜 高堂和拜 对方的名字’。”\n");
           CHANNEL_D->do_channel(moon, "mudnews",
                                 sprintf("恭贺%s和%s喜结良缘，拜堂大礼即时开始！\n", me->name(), obj->name()));
        set_temp("pending/bai", 1, me);
           set_temp("pending/bai", 1, obj);
        return 1;
}

int do_back(object ob)
{
           delete_temp("wait_time", ob);
           delete_temp("marry/money", ob);
        say("红娘拍了拍身上，又一扭一扭地向西边走去。\n");
           ob->move("/d/suzhou/hongniang-zhuang");
        return 1;
}

int do_bai(string arg)
{
        object me, ob, obj;

        me = this_player();
           ob = this_object();
        if (me->is_busy())
                return notify_fail("红娘说道：“你现在不是正忙着吗？忙完再说！”\n");

        if (me->is_fighting(this_object()))
        {
                if (! this_object()->is_killing(me))
                        this_object()->kill_ob(me);
                return notify_fail("红娘说道：“老娘好心给你办婚事，你敢动武，送你去阴间成婚吧！”\n");
        }

        if (this_object()->is_fighting())
                return notify_fail("红娘说道：没看见这儿有人捣乱吗！\n");

        if (! living(this_object()))
                return notify_fail("你还是先想办法把红娘救醒吧。\n");

        if (me->is_fighting())
                return notify_fail("红娘说道：“嘿嘿，你先还是料理完你的朋友再说吧！”\n");

        if (! environment() || base_name(environment()) != ("/d/suzhou/yinyuan-tang"))
                return notify_fail("红娘说道：“你这人真是的，拜堂是要到姻缘堂才行的呀！”\n");

        if( !query_temp("pending/bai", me) )
                return notify_fail("红娘笑道：“哈哈，你犯什么傻呀！”\n");

        if( !objectp(obj=present(query("couple/id", me),environment(me)) )
         || !find_player(query("couple/id", me)) )
        {
                   message_vision("红娘转身一看，惊讶地说道：“唉呀！你的爱人怎么突然跑了？婚礼怎么举行？大伙散摊吧。”\n"
                                     "在一片惋惜声，大家纷纷离场，喜堂上的东西也是一收而空。\n", me);
                      call_out("do_back", 1, ob);
                      return 1;
           }

           if( arg == "天地" || arg == "高堂" || arg == ""+query("couple/name", me) )
                return notify_fail("“拜”与后面的词之间请用半角空格。\n");

        if( !arg || (query_temp("pending/bai", me) == 1 && arg != "天地" )
         || (query_temp("pending/bai", me) == 2 && arg != "高堂" )
         || (query_temp("pending/bai", me) == 3 && arg != query("couple/name", me)) )
                return notify_fail("红娘笑道：“你乱拜什么呀？一拜天地！二拜高堂！三拜你的爱人！可别再错了！”\n");

        if( query_temp("pending/act", obj) != arg )
        {
                      if( query_temp("pending/bai", me) != 3 )
                      {
                        tell_object(obj, MAG "你的伴侣正等着和你拜 " + arg + " 呢...\n" NOR);
                        write(MAG "现在你正等待着你的伴侣...\n" NOR);
                        set_temp("pending/act", arg, me);
                      }
                      else
                      {
                        tell_object(obj, MAG "你的伴侣正等着和你互拜（拜他的名字）呢...\n" NOR);
                        write(MAG "现在你正等待着你的伴侣...\n" NOR);
                        set_temp("pending/act", me->name(), me);
                      }
                return 1;
        }
        else if( query_temp("pending/bai", me) == 1 )
           {
                  message_vision("“一拜…天…地……”$N和$n在阵阵鼓乐声中盈盈拜下......\n", me, obj);
                      addn_temp("pending/bai", 1, me);
                      addn_temp("pending/bai", 1, obj);
                      return 1;
           }
        else if( query_temp("pending/bai", me) == 2 )
           {
                  message_vision("“二拜…高…堂……”$N和$n在站起来相视一笑，又缓缓拜下......\n", me, obj);
                      addn_temp("pending/bai", 1, me);
                      addn_temp("pending/bai", 1, obj);
                      return 1;
           }
        else if( query_temp("pending/bai", me) == 3 )
           {
                  message_vision("“夫妻…对…拜……”$N和$n在相互深深拜了一拜......\n", me, obj);
                message_vision(HIY "月老笑呵呵地说道：“好，$N和$n，现在正式结为夫妻! \n" NOR, obj, me);
                CHANNEL_D->do_channel(this_object(), "chat",
                        sprintf("恭喜%s和%s，一对璧人喜结良缘。\n            各位亲朋好友，可携礼到汝州喜福堂参加他们的婚宴！\n",
                                me->name(), obj->name()));
                                
                      set_temp("married_party", 1, me);//做上记号，喜来福老板看到就会同意开酒席
                      set_temp("married_party", 1, obj);//两人都做，但只有男性才有用

                      delete_temp("pending/bai", me);
                      delete_temp("pending/bai", obj);
                      delete_temp("pending/act", me);
                      delete_temp("pending/act", obj);

                   call_out("last_marry", 1, ob, me, obj);
                return 1;
           }
}

int last_marry(object ob, object me, object obj)
{
        object moon, room;
        if (! (room = find_object("/d/suzhou/yinyuan-tang")))
                room = load_object("/d/suzhou/yinyuan-tang");
        moon = present("yue lao", room);
        moon->move("/u/lonely/workroom");
           delete_temp("wait_time", ob);
           delete_temp("marry/money", ob);
        say("红娘喊道：“轿夫！快将新人送到喜福堂举行婚宴，我和月老就不去了，呵呵！”\n说完一扭一扭地向西边走去。\n");
           ob->move("/d/suzhou/hongniang-zhuang");
        message_vision(HIR "伴郎伴娘拥着两位新人，上了门口的两顶大红花轿，只听轿夫们一声“起轿！”\n"
                          "一行人吹吹打打地奔向喜福堂......\n" NOR, me, obj);
           me->move("/d/suzhou/jiao1");
           obj->move("/d/suzhou/jiao2");
        call_out("go_lou", 8, ob, me, obj);
        call_out("do_back", 10, ob);
        return 1;
}

int go_lou(object ob,object me,object obj)//到酒楼
{
        object room, npc;
        
        if (! (room = find_object("/d/suzhou/xifu-tang")))
                room = load_object("/d/suzhou/xifu-tang");
                
        message_vision("\n    过了好长一会儿，只听轿夫们一声“到啦！”轿子整个儿一震，想是落到了地上，\n"
                   "$N和$n从轿子中下来一看，原来已经到了喜福堂。两人又被拥扶着一直上了二楼福满堂。\n"
                      "只听到一阵呵呵笑声，喜福堂老板喜来福笑容满面地迎出来：“恭喜两位新人！恭喜恭喜！\n”", me, obj);
                      
           npc = new("/d/suzhou/npc/xi-laifu");
           set("name1", me->name(), npc);
           set("name2", obj->name(), npc);//双方姓名
           npc->move(room);
           me->move(room);
           obj->move(room);
           return 1;
}

int do_witness(object me, object ob)
{
        message_vision("$N含情脉脉的望着$n，真是柔情似水，过了良久才对" +
                       name() + "道：这位小姑娘能否为我们证婚？\n\n",
                       me, ob);
                       
        if (! living(ob))
        {
                message_vision(name() + "吃吃的掩嘴而笑，对$N道：我"
                               "看你还是先把这位弄醒再说吧。\n", me);
                return 1;
        }

        if (! userp(ob))
        {
                message_vision(name() + "满脸都是苦笑，笑啥"
                               "呢？你也呵呵的跟着傻笑。\n", me);
                return 1;
        }

        message_vision(name() + "大声喊道：“很好啊，好得很！俗"
                       "话说：“在天愿为比翼鸟，在地愿成连理枝。”\n" +
                       "促成良缘是天大的美事！我" + name() + "最愿意了，问题是这位" +
                       RANK_D->query_respect(ob) + "也愿意吗？”\n\n", me);

        tell_object(ob, YEL + name() + "悄声问你：" + me->name(1) +
                        "在向你求婚呢，你答应(right)还是不答应(refuse)？\n" NOR);
        ob->set_temp("pending/answer/"+query("id", me)+"/right",
                     bind((: call_other, __FILE__, "do_right", ob, me :), ob));
        ob->set_temp("pending/answer/"+query("id", me)+"/refuse",
                     bind((: call_other, __FILE__, "do_refuse", ob, me :), ob));
        set_temp("pending/engage", ob, me);
        return 1;
}

int do_right(object me, object ob)
{
        string fn;
        string fc;
        object ring;

        message_vision("$N偷偷看了看$n，使劲的点头道：我愿意，愿意极了！\n" + name() +
                       "听了，笑嘻嘻道：“两厢情愿，又有我这媒人，那还不好办吗？”\n\n",
                       me, ob);
        command("chat 恭喜" + me->name(1) + "和" + ob->name(1) +
                 "成为百年之好！");
        message("visoin", name() + "笑着对二人说：“今个儿是你们"
                "大喜的日子，我没有什么礼物，只好送给你"
                "们这对新人一对结婚戒指吧！”\n\n", environment(me));

        fc = read_file(MARRY_RING);
        fc = replace_string(fc, "LONG_DESCRIPTION",
                            "这是" + me->name(1) + "和" +
                            ob->name(1) + "的结婚戒指，是两人的定情之物。\n");

        // give ring to me
        fn=RING_DIR+query("id", me);
        if (file_size(fn + ".c") > 0)
        {
                if (ring = find_object(fn)) destruct(ring);
                rm(fn + ".c");
        }
        assure_file(fn);
        write_file(fn + ".c", fc);
        VERSION_D->append_sn(fn + ".c");
        ring = load_object(fn);
        ring->move(me, 1);
        tell_object(me, HIY "你获得了一个结婚戒指。\n" NOR);
        set("can_summon/"+"weddingring", fn, me);

        // give ring to ob
        fn=RING_DIR+query("id", ob);
        if (file_size(fn + ".c") > 0)
        {
                if (ring = find_object(fn)) destruct(ring);
                rm(fn + ".c");
        }
        assure_file(fn);
        write_file(fn + ".c", fc);
        VERSION_D->append_sn(fn + ".c");
        ring = load_object(fn);
        ring->move(ob, 1);
        tell_object(ob, HIY "你获得了一个结婚戒指。\n" NOR);
        set("can_summon/"+"weddingring", fn, ob);
        
        // record
        set("couple/id",query("id",  ob), me);
        set("couple/name", ob->name(1), me);
        set("couple/witness", name(), me);
        me->save();
        set("couple/id",query("id",  me), ob);
        set("couple/name", me->name(1), ob);
        set("couple/witness", name(), ob);
        ob->save();
        set_temp("ask_money", 1, me);
        set_temp("ask_money", 1, ob);
        tell_object(me, HIR "你们如果想把这次结婚搞的风光点，你只要给我 1000 gold，我可以帮你们张罗所有的事情。\n" NOR);
        tell_object(ob, HIR "你们如果想把这次结婚搞的风光点，你只要给我 1000 gold，我可以帮你们张罗所有的事情。\n" NOR);
        return 1;
}

int do_refuse(object me, object ob)
{
        message_vision("$N瞥了$n一眼，转过头去不再看，连吐了"
                       "几口，“呸、呸、我呸呸呸！”\n" +
                       name() + "无奈的对$n道：“你也看到了，"
                       "俗话说强扭的瓜不甜啊...”\n", me, ob);
        return 1;
}

int do_divorce(object me)
{
        object ob;

        if( query("couple/witness", me) != name() )
        {
                message_vision(name() + "摇摇头，对$N道：“我可"
                               "不是你们的媒人，你们要离就离，别来烦我！”\n", me);
                return 1;
        }

        ob=find_player(query("couple/id", me));
        if (! ob || environment(ob) != environment(me))
        {
                message_vision(name() + "吃惊的看着$N道：“怎么，吵"
                               "架了？唉，花无百日好啊！不过要离你怎"
                               "么也得把人家找来一起谈谈啊！”\n", me);
                return 1;
        }

        if (! living(ob))
        {
                message_vision(name() + "摇摇头，对$N道：“我说这位" +
                               RANK_D->query_respect(me) +
                               "，怎么也得等人家醒过来再说吧！”\n", me);
                return 1;
        }

        if( query_temp("pending/submit_divorce", me) )
        {
                message_vision(name() + "摇摇头，对$N道：“你着"
                               "什么急，也不看看人家的意思？”\n",
                               me);
                return 1;
        }

        if( !query_temp("pending/submit_divorce", ob) )
        {
                message_vision(name() + "轻轻叹了口气，一张幼稚的脸上也"
                               "不禁有些沧桑，回头看了看$n，问道：“你"
                               "也是铁了心不和" + ob->name() + "过了？”\n\n", me, ob);
                tell_object(ob, YEL + name() + "悄悄的告诉你：要是那样，你就输入("
                                "divorce"+query("id", me)+")表示决心已定。\n");
                set_temp("pending/submit_divorce", 1, me);
                return 1;
        }

        message_vision(name() + "痛心的对$N和$n道：“当初我为你们"
                       "两个做媒的时候，可真没想到会有这么一天！”\n\n", me, ob);
        command("chat 从今天起" + me->name(1) + "和" + ob->name(1) +
                "分手了，以后可就各走各的路啦！");
        UPDATE_D->clear_user_data(query("id", me),"couple");
        return 1;
}

int accept_fight()
{
        command("fear");
        command("say 别来，我好怕怕的。");
        return notify_fail("你还是算了吧！\n");
}

int accept_hit()
{
        command("say 不要啊！不要乱动手！");
        return notify_fail("你还是算了吧！\n");
}

int accept_kill()
{
        command("say 呀！你想干什么？");
        return 1;
}

void unconcious()
{
        die();
}

void die()
{
        command("chat 不好了！出人命了！");
        message_vision("$N飞也似的逃走了。\n", this_object());
        destruct(this_object());
}

int return_home(object home) // 防止婚礼中更新，红娘回家
{
        if (! environment() || environment() == home) 
                return 1;
        if (! living(this_object()) ||  is_fighting()) 
                return 0;
        if( query_temp("wait_time", this_object()) )
                return 0; // 有结婚的参数就不回去

        message("vision", this_object()->name() + "急急忙忙地离开了。\n",
                    environment(), this_object());
        return move(home);
}
