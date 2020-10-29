// skybook.c 十四天书任务相关指令

#include <ansi.h>

inherit F_CLEAN_UP;

int help(object me);

mapping skybooks = ([

        "1" : "飞狐外传:★★★☆",
        "2" : "雪山飞狐:★★★☆",
        "3" : "连城诀:★★★",
        "4" : "天龙八部:★★★★★",
        "5" : "射雕英雄传:★★★★★",
        "6" : "白马啸西风:★★★",
        "7" : "鹿鼎记:★★★★",
        "8" : "笑傲江湖:★★★★★",
        "9" : "书剑恩仇录:★★★★",
        "10" : "神雕侠侣:★★★★★",
        "11" : "侠客行:★★★★☆",
        "12" : "倚天屠龙记:★★★★★",
        "13" : "碧血剑:★★★★☆",
        "14" : "鸳鸯刀:★★★☆",
]);

// 用于对应天书的管理OB，每本天书对应1个管理OB
mapping skybook_id = ([
        "飞狐外传"    : "feihuwaizhuan",
        "雪山飞狐"    : "xueshanfeihu", 
        "连城诀"      : "lianchengjue", 
        "天龙八部"    : "tianlongbabu",
        "射雕英雄传"  : "shediaoyingxiongzhuan",
        "白马啸西风"  : "baimaxiaoxifeng",
        "鹿鼎记"      : "ludingji",
        "笑傲江湖"    : "xiaoaojianghu",
        "书剑恩仇录"  : "shujianenchoulu",
        "神雕侠侣"    : "shendiaoxialv", 
        "侠客行"      : "xiakexing",    
        "倚天屠龙记"  : "yitiantulongji",
        "碧血剑"      : "bixuejian",
        "鸳鸯刀"      : "yuanyangdao",
]);

void create() 
{
        seteuid(getuid());

}

int main(object me, string arg)
{
        string sBook, msg, sDiff, sJindu, sNandu, ssk;
        int i;
        mixed *mFile;

        if( !arg ) return help(me);
                
        if( arg == "list" )
        {
                msg =  HIY "\n你翻开十四天书，发现记载了以下内容…………\n" NOR;
                msg += HIC"----------------------------------------------------------------------------\n" NOR;
                msg +=  sprintf(HIG "%-20s%-20s%-20s%-20s\n" NOR, "天书", "难度", "当前状态", "当前难度");
                msg += HIC"----------------------------------------------------------------------------\n" NOR;
                
                for( i=0; i<sizeof(skybooks); i++ )
                {
                        sscanf(skybooks[sprintf("%d", i+1)], "%s:%s", sBook, sDiff);
                        // 完成进度，首先判断是否激活
                        if( !query("skybook14/" + sBook + "/激活", me) )
                        {
                                sJindu = NOR + WHT "未激活" NOR;
                        }
                        else
                        {
                                // 激活了，判断是否已经接了任务
                                if( !query("skybook14/" + sBook + "/当前章节", me) )
                                        sJindu = HIR "已激活" NOR;
                                else
                                        sJindu = HIG + query("skybook14/" + sBook + "/当前章节", me) + NOR;
                        }
                        
                        // 如果完成了大结局，则显示副本状态为完成
                        if( query("skybook14/" + sBook + "/当前章节", me) == "大结局" )
                                        sJindu = HIY "已完成" NOR;

                        sBook = HIG + sBook[0..1] + NOR + sBook[2..(sizeof(sBook)-1)];
                        // 获取选择的难度
                        sNandu = query("skybook14/" + filter_color(sBook) + "/难度", me);
                        
                        if( sNandu == 0 )sNandu = "未激活";

                        sJindu = filter_color(sJindu);
                        

                        if( sJindu == "未激活" )
                        {
                                sJindu = NOR + HIR + sJindu + NOR;
                                sNandu = NOR + HIR + sNandu + NOR;
                        }
                        else if( sJindu == "已完成" )
                        {
                                sJindu = NOR + HIY + sJindu + NOR;
                                sNandu = NOR + HIY + sNandu + NOR;
                        }
                        else
                        {
                                sJindu = NOR + HIG + sJindu + NOR;
                                sNandu = NOR + HIG + sNandu + NOR;
                        }
                        
                        msg += sprintf("%-20s%-20s%-20s%-20s\n", sBook, sDiff, sJindu, sNandu);
                }

                msg += HIC"----------------------------------------------------------------------------\n" NOR;
                msg += HIY"skybook cha <天书名> 可查看天书详情\n" NOR;
                msg += HIY"skybook jihuo <天书名> <少侠级/大侠级/宗师级>   可激活\n" NOR;
                msg += HIY"skybook reset <天书名> 可重置天书\n" NOR;
                msg += HIY"skybook start <天书名> 可继续天书任务\n" NOR;        
                msg += HIC"----------------------------------------------------------------------------\n" NOR;
                msg += HIG"当前剩余气运：" + 
                        sprintf(HIY "%d/%d点" HIG, query("skybook14/option/luck",me),100) + 
                        "，每次挑战天书副本都将消耗３点气运值\n" NOR;
                msg += HIG"每１２小时（无需在线）可恢复１点气运值，气运值上限为１００点。\n" NOR;

                write(msg);
                return 1;
        }
        
        if( sscanf(arg, "cha %s", sBook) == 1 )
        {
                if( !query("skybook14/" + sBook + "/激活", me) )
                        return notify_fail(sBook + "还未激活，请用 " HIG + "skybook jihuo " + sBook + " <少侠级/大侠级/宗师级> " NOR" 激活\n");
                        
                if( query("skybook14/" + sBook + "/当前章节", me) == 0)
                        return notify_fail(sBook + "还未开始，请用 " HIG + "skybook start " + sBook + NOR " 开始\n");

                msg = HIY + "\n" + sBook + "天书记载了以下内容…………\n" NOR;
                msg += HIC"----------------------------------------------------------------\n" NOR;             
                if( query("skybook14/" + sBook + "/当前章节", me) == "大结局")
                {
                        msg += HIR + "《"  + sBook + "》已经完成，若需重新开启，可使用 " HIG + "skybook reset " + sBook + HIR " 重置！\n";
                }
                else
                {
                        msg += HIY "当前章节：" + query("skybook14/" + sBook + "/当前章节", me) + "\n" NOR;
                        msg += HIY "任务描述：" HIG + query("skybook14/" + sBook + "/当前任务", me) + "\n" NOR;
                        //msg += HIY "关卡名称：" HIG + query("skybook14/" + sBook + "/当前标题", me) + "\n" NOR;
                        if( wizardp(me) )
                                msg += HIY "任务编号：" + query("skybook14/" + sBook + "/任务编号", me) +  "\n" NOR;
                        msg += HIY "任务状态：" + (query("skybook14/" + sBook + "/任务状态", me) == 1 ? HIG "已完成" NOR: HIC "进行中" NOR) + "\n" NOR;
                        msg += HIY "当前难度：" + query("skybook14/" + sBook + "/难度", me) + "\n" NOR;
                }
                msg += HIC"----------------------------------------------------------------\n" NOR;
                msg += HIY"请输入 " HIG + "skybook start " + sBook + HIY " 来继续天书任务！\n\n" NOR;           
                write(msg);
                return 1;
        }
        if( sscanf(arg, "jihuo %s %s", sBook, sNandu) == 2 )
        {
                string *get2kskills, *keys_myskills;
                mapping getmyskills;
                
                if( !wizardp(me) ) return notify_fail("暂时未开放，敬请期待！\n");
                
                if( query("skybook14/" + sBook + "/激活", me) )
                        return notify_fail(sBook + "已经激活了！\n");
                
                if( query("yuanshen_level", me) < 100 )
                        return notify_fail("你还没有修炼成元神到不灭境界，无法激活天书，修炼元神说明见 help yuanshen\n");
                
                
                if( sNandu != "少侠级" && sNandu != "大侠级" && sNandu != "宗师级" )
                        return notify_fail("天书的难度选择只能是 少侠级、大侠级、宗师级中的一项！例如:skybook jihuo 笑傲江湖 宗师级\n");
                
                
                // 不同天书不同激活条件
                switch(sBook)
                {
                         case "连城诀":
                                 set("skybook14/" + sBook + "/激活", 1, me);
                                 set("skybook14/" + sBook + "/难度", sNandu, me);
                                set("skybook14/" + sBook + "/任务编号", 1, me);
                                 break;
                         case "笑傲江湖":
                                
                         if( query("skybook14/" + sBook + "/激活条件", me) )
                         {
                                if( !query_temp("pending_skybook/" + sBook, me) )
                                {
                                        set_temp("pending_skybook/" + sBook, 1, me);
                                        write(HIG "激活" HIY + sBook + HIG "将损耗你的" + HIY + 
                                              CHINESE_D->chinese(query("skybook14/" + sBook + "/激活条件", me)) + HIG +
                                              "１００级，如果确定请再输入一次该指令！\n" NOR);
                                        
                                        return 1;
                                }
                                
                                delete_temp("pending_skybook/" + sBook, me);
                                
                                // 降低技能，开始激活
                                me->add_skill(query("skybook14/" + sBook + "/激活条件", me), -200);
                                
                                set("skybook14/" + sBook + "/激活", 1, me);
                                
                                write(BLINK + HIG "\n天书" HIY + sBook + HIG "已激活，输入 skybook start " + sBook + " 开启序章！\n" NOR);

                                // 初始化
                                set("skybook14/" + sBook + "/当前章节", "第一章", me);
                                set("skybook14/" + sBook + "/当前标题", "路见不平", me);
                                set("skybook14/" + sBook + "/当前任务", "输入 skybook start " + sBook + " 打开天书序幕吧!", me);
                                set("skybook14/" + sBook + "/难度", sNandu, me);
                                set("skybook14/" + sBook + "/任务编号", "1", me);

                                __FILE__->main(me, "cha " + sBook);

                                log_file("0激活天书.log", me->query_idname() + "激活" + sBook + " 降低技能 " + 
                                         query("skybook14/" + sBook + "/激活条件", me) + " At " + ctime(time()) + "\n");
                                
                                delete("skybook14/" + sBook + "/激活条件", me);
                                return 1;
                         }

                        // 大于1500LV的技能随机降低200级，若没有大于1500的技能，则不能激活
                        getmyskills = me->query_skillc();                       
                        if( !sizeof(getmyskills) ) return notify_fail("你连技能都没有学，还想闯天书？\n");
                        keys_myskills = keys(getmyskills);
                        get2kskills = ({});
                        for( i=0; i<sizeof(keys_myskills); i++ )
                                if( getmyskills[keys_myskills[i]] >= 1500 )
                                        get2kskills += ({ keys_myskills[i] });

                        if( !sizeof(get2kskills) )
                                return notify_fail("激活《" + sBook + "》天书至少需要一项技能达到１５００级！\n");

                        set_temp("pending_skybook/" + sBook, 1, me);

                        // 随机选择1个需要损耗的技能
                        ssk = get2kskills[random(sizeof(get2kskills))];
                        if( ssk == "martial-cognize" && random(10) < 7 ) ssk = get2kskills[random(sizeof(get2kskills))];
                                
                        set("skybook14/" + sBook + "/激活条件", ssk, me);

                        write(HIG "激活" HIY + sBook + HIG "将损耗你的" + HIY + 
                              CHINESE_D->chinese(query("skybook14/" + sBook + "/激活条件", me)) + HIG +
                              "２００级，如果确定请再输入一次该指令！\n" NOR);

                        return 1;
                        break; // up 笑傲江湖
                        
                        case "雪山飞狐" :
                        break;
                default:
                        return notify_fail(sBook + "天书不存在或暂未开放！\n");

                }// switch
                
                return 1;
        }

        if( sscanf(arg, "start %s", sBook) == 1 )
        {
                object obtianshu;
                string sTianshu;
                
                if( me->is_fighting() || me->is_busy() )
                        return notify_fail("你正忙着呢，等下再试吧！\n");
                
                if( !query("skybook14/" + sBook + "/激活", me) )
                        return notify_fail(sBook + "还未激活，请用 " HIG + "skybook jihuo " + sBook + NOR " <难度:少侠级/大侠级/宗师级>  来激活\n");   

                if( query("skybook14/" + sBook + "/当前章节", me) == "大结局")
                        return notify_fail(sBook + "已经完成，若需重新开启，可使用 " HIG + "skybook reset " + sBook + NOR " 重置！\n");
                        
                // 交给天书OB管理
                sTianshu = skybook_id[sBook];
                if( !objectp(obtianshu = find_object("/adm/daemons/skybook/" + sTianshu)))
                        obtianshu = load_object("/adm/daemons/skybook/" + sTianshu);

                if( !objectp(obtianshu) ) return notify_fail("天书管理OB错误，请联系新手导师或管理员处理！\n");

                // 判断体力和扣除体力
                if( query("skybook14/option/luck", me) < 3 )
                        return notify_fail("当前气运不足，无法开始天书副本！可使用指令" HIY "ntstore buy luck" NOR "购买气运全满（价格见ntstore show other）！\n");

                addn("skybook14/option/luck", -3, me);
                
                tell_object(me, HIY"\n剩余气运：" + sprintf("%d/100", query("skybook14/option/luck", me)) + "\n" NOR);

                obtianshu->startbook(me, sBook);

                return 1;
                
        }
        if( sscanf(arg, "reset %s", sBook) == 1 )  // 每次重置需要消耗特殊材料
        {
                if( !query("skybook14/" + sBook + "/激活", me) )
                        return notify_fail(sBook + "还未激活，请用 " HIG + "skybook jihuo " + sBook + NOR " 激活\n");   
                /*
                if( query("skybook14/" + sBook + "/当前章节", me) != "大结局" )
                        return notify_fail(sBook + "还未完成，不能重置！\n");   
                */      
                // 重置需要消耗NT
                if( MEMBER_D->db_query_member(me, "money") < 99)
                {
                        return notify_fail("重置天书需要花费 99 NT币，你没有足够的剩余NT币！\n");
                }
                
                if( !query_temp("pending_reset/" + sBook, me) )
                {
                        write(HIG "重置" + HIY + sBook + HIG "需要花费 99 NT币，如果你确定请再输入一次该指令！\n" NOR);
                        set_temp("pending_reset/" + sBook, 1, me);
                        
                        return 1;
                }

                delete_temp("pending_reset/" + sBook, me);

                // 扣除NT
                MEMBER_D->player_pay(me, 99);

                log_file("0天书重置.log", me->query_idname() + " 重置 " + sBook + " at " + ctime(time()) + "\n");
                
                delete("skybook14/" + sBook, me);
                me->save();

                // 重置后不用帮忙激活
                set("skybook14/" + sBook + "/激活", 0, me);

                write("重置" + sBook + "完毕！\n");

                return 1;
        }       
        
        if( wizardp(me) && sscanf(arg, "enddialog %s %d", sBook, i) == 2 )  // 测试指令，用于巫师直接跳过剧情对话
        {
                object obroom;
                
                if (! objectp(obroom = find_object("/adm/daemons/skybook//" + sBook + "/" + sBook)))
                        obroom = load_object("/adm/daemons/skybook//" + sBook + "/" + sBook);                

                obroom->dialog_end(me, i);
                return 1;
        }
}

int help(object me)
{
        write(@HELP
指令格式 : skybook

skybook list                                       ：查看十四天书总览
skybook cha <天书中文名>                           ：查看对应的天书详情
skybook jihuo <天书中文名> <少侠级/大侠级/宗师级>  ：激活对应难度的天书
skybook start <天书中文名>                         ：继续上次未完的天书任务
skybook reset <天书中文名>                         ：当天书完成后，可重置天书后重新再做一次该天书任务

HELP );
    return 1;
}

