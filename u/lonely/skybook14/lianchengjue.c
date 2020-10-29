#include <ansi.h>

#define DB_D          "/adm/daemons/dbd"
#define DIALOG_D      "/adm/daemons/dialogd"
#define SUICONG_D     "/adm/daemons/suicongd"
#define SKYBOOK_D     "/adm/daemons/skybookd"

inherit ITEM;

string *sBookMsg1 = ({
        "你翻开《连城诀》，瞬间，一道金光将你笼罩，古旧的书页上，显出一行行小字 ……",
        "《连城诀》乃金庸先生创作于1963年，刊载于《东南亚周刊》，书名本做《素心剑》，之后改名为《连城诀》。",
        "此书语言质朴生动，情节紧凑，故事感人，全书充满了一股悲愤之气，读来令人如鲠在喉。",
        "《连城诀》写世态，写人心，写至情至爱，动人心魄，远远超出了一般武侠小说的表现范畴，甚至亦非“性情”二字所能概括，可说是金庸作品中的奇特之作。 ",
        "现在，你将扮演书中主角狄云的身份，进入《连城诀》天书中体验另外一番奇特的故事，准备好了吗，正式进入天书世界 ……        ",
        "=---------------------------------  连城诀  ---------------------------------=",
        HIY "《序章》" NOR,
        "你出生在湘南一户普通农村，自幼父母双亡，后机缘巧合，被一位武艺高强的老者收养为弟子，这位老者叫戚长发，你一直叫他师父。",
        "师父从小把你养大成人，教你武艺，待你如亲生，你也对师父犹如亲生父亲一般，感情颇为深厚。",
        "师父有个女儿，叫戚芳，生得清秀可人，比你年纪小两岁，你叫她师妹，从小你二人青梅竹马，无话不谈，虽未明示，却早已认定对方为终身伴侣。",
        "你师徒三人，虽生活在农村，可每日务农练剑，与师父海阔天遥，与师妹切磋逗趣，生活得犹如世外桃源一般，好不快活，对江湖上的事情是一无所知。",
        "这一日清早，与往常一样，师父唤你兄妹二人前去切磋武艺 ……",
});

string *sBookMsg2 = ({
        HIC "你学会了【唐诗剑法】！" NOR,
        "今日，师傅戚长发继续让你和戚芳二人练习唐诗剑法，这剑法自打下就和师妹一起学习，乃师傅的绝学。",
        "戚长发道：为师传你这套唐诗剑法，你练得还不够纯熟，一定要多加练习！" ,
        "你应道：是！徒儿一定勤奋练习！",
        "戚长发点头道：好！好！那为师过几日再来考校！ ",
        HIC "将【唐诗】剑法提升到500级后再来(任务完成后输入skybook start 连城诀)" NOR,
});

string *sBookMsg3 = ({
        HIG "任务达成！" NOR,
        "你恭恭敬敬地向师傅戚长发磕头道：师傅，徒儿的唐诗剑法已经练得纯熟了，请师傅考校。",
        "戚长发道：不错不错！你且和芳儿切磋一下，为师从旁看看你二人最近的功夫如何。" ,
        "你应道：是！",
        HIC "接受到新的任务：输入 skybook cha 连城诀 查看任务描述！" NOR,
});

string *sBookMsg4 = ({
        HIG "任务达成！" NOR,
        HIY "《第一章》寿宴" NOR,
        "戚长发突然跳出，手中竹竿将你震开 ……",        
        "戚长发道：徒儿武功大有长进，可是还未做到收发自如，以后还得勤加练习，切勿伤人。",
        "你说道：是，师傅！",
        "戚芳：师哥老是欺负我，不练了！",
        "你呵呵笑道：师妹别生气，以后师哥让着你就是了。",
        "戚长发道：天气逐渐转凉了，这山野之地寒气颇重，徒儿有空去打些白狐皮回来，让芳做几件皮袄过冬。",
        "你说道：是，徒儿这就去！",
        HIC "接受到新的任务：输入 skybook cha 连城诀 查看任务描述！" NOR,
});

string *sBookMsg5 = ({
        "戚芳接过你手中的白狐皮大喜：师哥，这白狐皮可是难得，做成皮袄可化雪与三尺之外  ……",
        "戚长发呵呵笑着让戚芳快去准备晚饭，明日赶制皮袄，你嚷嚷道去帮师妹洗菜  ……",   
        "师徒三人有说有笑，一骑快马疾驰而来 ……",
        "马上那人驶到门前下马，对戚长发道：敢问这位老者是否戚长发戚师叔？",
        "戚长发道：来者何人？",
        "那人道：原来真是戚师叔，弟子周圻，乃万震山徒弟。",
        "戚长发道：我道是谁，原来是大师兄的弟子，说那么多年不见，找我何事？",
        "周圻道：师傅下月寿辰，在荆州万府设宴，让我来请师叔赴宴！",
        "戚长发道：我和大师兄二十年不见，怎地这次寿宴就来请我了，好好，你回去吧，告诉他我一定来。",
        "周圻应道：“是！” 扬鞭快马而去！",
        "戚长发：芳儿，徒儿，好好收拾一下细软，过几日咱们要进城了，给你大师伯拜寿！",
        "你和戚芳同时说道：是！",
        HIC "接受到新的任务：输入 skybook cha 连城诀 查看任务描述！" NOR,
});

string *sBookMsg6 = ({
        "你师徒三人经过半月路程，终于来到了荆州，几经打听找到万府  ……",
        "只见这万府门庭宽阔，朱墙高瓦，一副大富大贵之气  ……", 
        "大门前张灯结彩，门庭若市，来往之人穿梭不断，好不热闹。",
        "门前一位约摸五十岁上下年纪的人，身着华服，对来往客人笑脸相迎，相必就是万震山了。",
        "你和戚芳自小在乡下长大，未见过这等世面，也不善与人交往，傻傻地站在一旁，师傅戚长发和万震山正说着话……",
        "突然间，一人跳出来对万震山大骂，说辞不堪入耳，话语间知道那人叫吕通，万震山当年与人结了梁子，今日人家来寻晦气。",
        "万震山道：大盗吕通，今日老夫寿辰，你我恩怨改日再论，再不速速离开，休怪我手下不留情。",
        "吕通道：万震山你个乌龟王八蛋，害我全家，今日必定与你拼个你死我活……",
        
        HIC "接受到新的任务：输入 skybook cha 连城诀 查看任务描述！" NOR,
});

string *sBookMsg7 = ({
        "见你击败大盗吕通后，万震山拱手道：“小兄弟好身手！”一旁的万震山弟子们脸露不悦。",
        "万震山的三徒弟乃他亲生儿子，相貌端正，只见他时不时地对着你身旁的戚芳偷看！",
        "万震山招呼宾朋入座，你和戚芳还有万震山的八个弟子坐一桌，席间众人对戚芳美色垂涎三尺，对你讥讽相加……",
        "宴散，人去，夜幕降临 ……",
        "你在客房中静坐，突然听到一声尖叫，你寻声飞奔过去，只见一个黑影窜进西面偏房。",
        "你紧跟着分身进入房间，只见房内一片漆黑，哪里有黑影，正犹豫间，背后猛地一击。",
        HIR "\n你眼前一黑，接着什么也不知道了 ……\n" NOR,
        HIC "接受到新的任务：输入 skybook cha 连城诀 查看任务描述！" NOR,
});

string *sBookMsg8 = ({
        "你悠悠醒转，只见屋内站满了人，又万震山的八个弟子，有家丁，戚芳也在一旁流着眼泪看着你 ……",
        "其中一个弟子道：想不到我家师傅请你们来赴宴，你却做出这等事情来，连师傅的小妾桃红你也非礼。",
        "另外一个弟子道：我看他们师徒定是有什么不可告人的目的，师傅被戚长发刺伤后重伤在床，戚长发到是溜得不见人影了。",
        "你正欲起身争辩，却发现自己已被五花大绑，浑身无力，你道：究竟怎么回事？师傅呢，桃红又是谁，师妹，这，这是怎么回事？",
        "戚芳道：他们，他们说你非礼桃红，他们说亲眼看到你跟进房来，他们还说师傅刺伤了万前辈逃跑了。",
        "说完，戚芳唰的流下眼泪 ……",
        "一个弟子道：你别装蒜了，我们早就看你不对劲，想不到你是这种人，干脆送官吧！",
        "“对，送官，送官”很多人附和。",
        "你大声道：师妹，你不相信我么，我是被冤枉的，你不相信我么？",
        "戚芳道：“师哥，我相信我信”说完只是低头流泪，不再做声！",
        "你心道：师妹定是也相信了这群人所说，自己莫大冤屈不知何处倾述，从小青梅竹马的师妹，单纯不更事，相必也相信了我这个师哥是个淫贼吧！",
        "你心里想着想着，悲戚万分！",
        "你正欲开口说话，又是后背猛的一击，你昏迷了过去！",
        HIR "\n你眼前一黑，接着什么也不知道了 ……\n" NOR,
        HIC "接受到新的任务：输入 skybook cha 连城诀 查看任务描述！" NOR,
});


string *sBookMsg9 = ({
        "不知过了多久，你悠悠醒转，竟然被关进了监狱，四处幽暗无比，虫鼠穿梭，臭味冲天 ……",
        "你想大声喊，却发现无法动弹，或者说一动弹就撕心裂肺地痛 ……",
        "你不断呻吟，发现自己竟被一跟粗大的铁链穿透了琵琶骨锁住，一动就痛彻心扉 ……",
        "狱卒过来狠狠地说道：你就在这里等死吧，不会有人来看你的，你居然得罪了万家，这辈子就别想出去了。",
        HIY "《第二章》牢狱" NOR,

        HIR "\n你眼前一黑，接着什么也不知道了 ……\n" NOR,
        HIC "接受到新的任务：输入 skybook cha 连城诀 查看任务描述！" NOR,
});


void create()
{
        set_name("天书", ({ "skybook lianchengjue" }));
        if (clonep())
                set_default_object(__FILE__);
        else {
                set("value", 0);
                set_weight(0);
        }
        setup();
}

void start_story(int book)
{
        if( book == 1 ) SKYBOOK_D->broadcast_story(this_player(), sBookMsg1, 0, 2);
        else if( book == 2 ) SKYBOOK_D->broadcast_story(this_player(), sBookMsg2, 0, 2);
        else if( book == 3 ) SKYBOOK_D->broadcast_story(this_player(), sBookMsg3, 0, 2);
        else if( book == 4 ) SKYBOOK_D->broadcast_story(this_player(), sBookMsg4, 0, 2);
        else if( book == 5 ) SKYBOOK_D->broadcast_story(this_player(), sBookMsg5, 0, 2);
        else if( book == 6 ) SKYBOOK_D->broadcast_story(this_player(), sBookMsg6, 0, 2);
        else if( book == 7 ) SKYBOOK_D->broadcast_story(this_player(), sBookMsg7, 0, 2);
        else SKYBOOK_D->broadcast_story(this_player(), sBookMsg8, 0, 2);
}

void start_story1()
{
        "/adm/daemons/skybookd.c"->broadcast_story(this_player(), sBookMsg2, 0, 2);
}

void start_story2()
{
        "/adm/daemons/skybookd.c"->broadcast_story(this_player(), sBookMsg3, 0, 2);
}

// 移动到剧情副本，根据flag 不同创造不同的剧情副本
// flag代表创建何种房间，比如叫什么名字的房间，里面有些什么NPC
// obx代表返回的创建房间后，同时创建里面的NPC，最后返回一个NPC的OB编号,若为1则返回ob1
object move_to_room(object me, int flag, int obx)
{
        object obroom;
        object ob1, ob2, ob3, ob4, ob5, ob6, ob7, ob8;
        
        switch(flag)
        {
        case 1: // 出生点，湘南茅屋前
                obroom = new("/clone/skybook14/sky14room");
                obroom->set_name(HIG + "小茅屋" + NOR, ({ "xiaomaowu" }));
              //obroom>set("long", "这里是北京城的地安门大街。街道是整整齐齐的杨树林，道上行人络绎不绝，\n车两马匹穿插其中。\n",");  
                obroom->set("long", "这里是湘南农村的一处农家小院，一个简陋的茅屋前摆放着一个石桌。\n"); 
                obroom->set("create_time", time());
                ob1 = new("/clone/skybook14/lianchengjue/npc/qichangfa");
                ob2 = new("/clone/skybook14/lianchengjue/npc/qifang");
                ob1->move(obroom);
                ob2->move(obroom);
                me->move(obroom);
        break;
        case 2: // 万府+吕通
                obroom = new("/clone/skybook14/sky14room");
                obroom->set_name(HIG + "万府门前" + NOR, ({ "xiaomaowu" }));
              //obroom>set("long", "这里是北京城的地安门大街。街道是整整齐齐的杨树林，道上行人络绎不绝，\n车两马匹穿插其中。\n",");  
                obroom->set("long", "这里是荆州万府，乃万震山府邸，四处朱墙高瓦，好不气派。\n"); 
                obroom->set("create_time", time());
                ob1 = new("/clone/skybook14/lianchengjue/npc/lvtong");
                ob1->move(obroom);
                me->move(obroom);
        break;
        
        case 3: // 万府 无NPC
                obroom = new("/clone/skybook14/sky14room");
                obroom->set_name(HIG + "万府门前" + NOR, ({ "xiaomaowu" }));
              //obroom>set("long", "这里是北京城的地安门大街。街道是整整齐齐的杨树林，道上行人络绎不绝，\n车两马匹穿插其中。\n",");  
                obroom->set("long", "这里是荆州万府，乃万震山府邸，四处朱墙高瓦，好不气派。\n"); 
                obroom->set("create_time", time());
                me->move(obroom);
        break;

        case 4: // 万府厢房 无NPC
                obroom = new("/clone/skybook14/sky14room");
                obroom->set_name(HIG + "厢房" + NOR, ({ "xiaomaowu" }));
              //obroom>set("long", "这里是北京城的地安门大街。街道是整整齐齐的杨树林，道上行人络绎不绝，\n车两马匹穿插其中。\n",");  
                obroom->set("long", "这里是万府西面的厢房，床上睡着一个女子，周围站满了万府的弟子和家丁。\n"); 
                obroom->set("create_time", time());
                ob1 = new("/clone/skybook14/lianchengjue/npc/qifang");
                ob1->move(obroom);              
                me->move(obroom);
        break;

        case 5: // 牢房 丁典
                obroom = new("/clone/skybook14/sky14room");
                obroom->set_name(HIG + "厢房" + NOR, ({ "xiaomaowu" }));
              //obroom>set("long", "这里是北京城的地安门大街。街道是整整齐齐的杨树林，道上行人络绎不绝，\n车两马匹穿插其中。\n",");  
                obroom->set("long", "这里是荆州大牢，专门关押重犯，四周臭气熏天，阴暗潮湿。\n"); 
                obroom->set("create_time", time());
                ob1 = new("/clone/skybook14/lianchengjue/npc/dingdian");
                ob1->move(obroom);
                me->move(obroom);
        break;

        default:return;
        }
        
        switch(obx)
        {
        case 1:return ob1;
        case 2:return ob2;
        case 3:return ob3;
        case 4:return ob4;
        case 5:return ob5;
        case 6:return ob6;
        case 7:return ob7;
        case 8:return ob8;                      
        default:return ob1;
        }
}

// 模拟对话完成后调用的入口函数，执行后续操作 me代表玩家，flag 代表编号，用于分辨不同的处理
void dialog_end(object me, int flag)
{
        object ob;
                
        if (! objectp(me))return;
        
        //tell_object(me, "flag = " + sprintf("%d", flag) + "\n");
                        
        switch(flag)
        {
        case 1:
                ob = move_to_room(me, 1, 1);
                DIALOG_D->start_dialog(ob, me, sBookMsg2, 0, 5);
                return;
        break;

        case 5:
                me->set("skybook14/连城诀/任务编号", 5);
                me->set_player_skill("tangshi-jian", 1);
                me->set("skybook14/连城诀/当前任务", "将唐诗剑法提升到500级（任务完成后输入skybook start 连城诀）");
                
                return;
        break;

        case 10:
                me->set("skybook14/连城诀/任务编号", 10);
                me->set("skybook14/连城诀/当前任务", "与师妹戚芳切磋武艺（fight qi fang）。");

                return;
        break;

        case 15:
                me->set("skybook14/连城诀/任务状态", 0);
                me->set("skybook14/连城诀/任务编号", 15);
                me->set("skybook14/连城诀/当前任务", "搜集白狐皮200张。");
                me->set("skybook14/连城诀/当前章节", "第1章");
                return;
        break;

        case 20:
                me->set("skybook14/连城诀/任务状态", 1);
                me->set("skybook14/连城诀/任务编号", 20);
                me->set("skybook14/连城诀/当前任务", "准备好后就准备前往荆州万府吧（skybook start 连城诀）");
                me->set("skybook14/连城诀/当前章节", "第1章");
                return;
        break;
        
        case 25:
                me->set("skybook14/连城诀/任务状态", 0);
                me->set("skybook14/连城诀/任务编号", 25);
                me->set("skybook14/连城诀/当前任务", "击败大盗吕通");
                me->set("skybook14/连城诀/当前章节", "第1章");

                ob = environment(me);
                
                return;
        break;  
        
        case 30:
                ob = move_to_room(me, 4, 1);
                me->set("skybook14/连城诀/任务状态", 0);
                me->set("skybook14/连城诀/任务编号", 30);
                me->set("skybook14/连城诀/当前任务", "输入start skybook 连城诀 继续剧情");

                return;
        break;          

        case 35:
                ob = move_to_room(me, 5, 1);
                me->set("skybook14/连城诀/当前章节", "第2章");
                me->set("skybook14/连城诀/任务状态", 0);
                me->set("skybook14/连城诀/当前任务", "输入start skybook 连城诀 继续剧情");
                me->set("skybook14/连城诀/任务编号", 35);

                return;
        break;          
        default:return;
        }
}

// 来自 /cmds/usr/skybook.c调用，开始天书任务
void startbook(object me, string sBook)
{
        int nQuest; // 当前任务编号
        string sZhangjie; // 当前章节
        object ob, ob2;

        sZhangjie = me->query("skybook14/" + sBook + "/当前章节");
        nQuest = me->query("skybook14/" + sBook + "/任务编号");

        switch(nQuest)
        {
        case 1: // 序章
                DIALOG_D->start_dialog4(this_object(), me, sBookMsg1, 0, 1);
                return;
        break;
        
        case 5:// 提升唐诗剑法到500LV
                if (me->query_skill("tangshi-jian", 1) < 500)
                {
                        tell_object(me, me->query("skybook14/连城诀/当前任务") + "\n");
                        return;
                }
                
                ob = move_to_room(me, 1, 1);

                DIALOG_D->start_dialog(ob, me, sBookMsg3, 0, 10);
                
                return;
        break;

        case 10: // 切磋打过戚芳后
                if (me->query("skybook14/连城诀/任务状态") != 1)
                {       
                        move_to_room(me, 1, 1); // 任务未达成，重新传送房间

                        tell_object(me, me->query("skybook14/连城诀/当前任务") + "\n");
                        return;
                }

                ob = move_to_room(me, 1, 1);

                DIALOG_D->start_dialog(ob, me, sBookMsg4, 0, 15);

                return;
        break;

        case 15: // 搜集到200张狐狸皮后
                if (me->query("skybook14/连城诀/任务状态") != 1)
                {       
                        object ob_hlp;
                        // 检查是否有200张狐狸皮，如果有则扣除
                        if (! objectp(ob_hlp = present("baihu pi", me)))
                        {
                                tell_object(me, me->query("skybook14/连城诀/当前任务") + "\n");
                                return;
                        }

                        if (base_name(ob_hlp) != "/clone/quarry/item/lipi2")
                                return;
        
                        if (ob_hlp->query_amount() >= 200)
                        {
                                ob_hlp->add_amount(-200);
                                if (ob_hlp->query_amount() < 1)destruct(ob_hlp);
                                tell_object(me, HIG "任务达成！\n" NOR); 
                        }
                        else
                        {
                                tell_object(me, me->query("skybook14/连城诀/当前任务") + "\n");
                                return;
                        }
                        
                        me->set("skybook14/连城诀/任务状态", 1);
                }

                ob = move_to_room(me, 1, 2);

                DIALOG_D->start_dialog(ob, me, sBookMsg5, 0, 20);

                return;

        break;
        
        case 20: // 前往荆州万府
                
                ob = move_to_room(me, 2, 1);

                DIALOG_D->start_dialog(ob, me, sBookMsg6, 0, 25);

                return;
        break;  
        
        case 25: // 击败大盗吕通
                                        
                if (me->query("skybook14/连城诀/任务状态") != 1)
                {
                        ob = move_to_room(me, 2, 1); // 任务未达成，重新传送房间

                        tell_object(me, me->query("skybook14/连城诀/当前任务") + "\n");
                        return;
                }
                
                // 任务达成
                ob = move_to_room(me, 3, 1);

                DIALOG_D->start_dialog4(this_object(), me, sBookMsg7, 0, 30);

                return;

        break;
        
        case 30: // 追黑影入厢房

                // 任务达成
                ob = move_to_room(me, 4, 1);

                DIALOG_D->start_dialog(ob, me, sBookMsg8, 0, 35);

                return;

        break;
                        
        case 35: // 入厢房被打晕

                // 任务达成
                ob = move_to_room(me, 5, 1);

                //DIALOG_D->start_dialog4(ob, me, sBookMsg8, 0, 40);

                return;

        break;

        default:
                tell_object(me, HIY "输入 skybook cha 连城诀 查看当前任务情况！\n" NOR);
                return;
        }
        
        
        
}
