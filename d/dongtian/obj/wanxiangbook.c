// This program is a part of NITAN MudLIB 
// redl 2013/11
#include <ansi.h>
#include <skill.h>

inherit ITEM;
inherit F_CLEAN_UP;

mapping *booklists = ({
                (["id":"baijin-jianqi",
                        "tname":"白金剑气",
                        "rate":2
                        ]),
                (["id":"xuanli-daogang",
                        "tname":"玄离刀罡",
                        "rate":2
                        ]),
                (["id":"jiuyin-shengong",
                        "tname":"九阴神功",
                        "rate":3
                        ]),
                (["id":"bluesea-force",
                        "tname":"南海玄功",
                        "rate":3
                        ]),
                (["id":"never-defeated",
                        "tname":"不败神功",
                        "rate":3
                        ]),
                (["id":"kuihua-mogong",
                        "tname":"葵花魔功",
                        "rate":3
                        ]),
                (["id":"houtu-shengong",
                        "tname":"厚土神功",
                        "rate":4
                        ]),
                (["id":"bingxin-jue",
                        "tname":"冰心决",
                        "rate":6
                        ]),
                (["id":"qingmu-zhenqi",
                        "tname":"青木真气",
                        "rate":9
                        ]),
                (["id":"taixuan-gong",
                        "tname":"太玄功",
                        "rate":20
                        ]),
                (["id":"xuanming-shengong",
                        "tname":"玄冥神功",
                        "rate":22
                        ]),
                (["id":"xuanming-zhang",
                        "tname":"玄冥神掌",
                        "rate":22
                        ]),
                (["id":"bizhen-qingzhang",
                        "tname":"碧针清掌",
                        "rate":20
                        ]),
                (["id":"zijinbagua-dao",
                        "tname":"紫金八卦刀",
                        "rate":20
                        ]),
                (["id":"sanfen-jianshu",
                        "tname":"三分剑术",
                        "rate":20
                        ]),
                (["id":"huanyin-zhi",
                        "tname":"幻阴指",
                        "rate":20
                        ]),
                (["id":"ningxue-shenzhao",
                        "tname":"凝血神爪",
                        "rate":20
                        ]),
                (["id":"huajia-su",
                        "tname":"化甲术",
                        "rate":37,
                        "fam":"全真教"
                        ]),
                (["id":"jingxin",
                        "tname":"静心",
                        "rate":45,
                        "fam":"峨嵋派"
                        ]),
                (["id":"jianyi",
                        "tname":"剑意",
                        "rate":37,
                        "fam":"华山派"
                        ]),
                (["id":"wudu-jing",
                        "tname":"五毒阱",
                        "rate":43,
                        "fam":"五毒教"
                        ]),
                (["id":"bingchan-gong",
                        "tname":"冰蚕功",
                        "rate":35,
                        "fam":"星宿派"
                        ]),
                (["id":"tianwei-zhengqi",
                        "tname":"天威正气",
                        "rate":37,
                        "fam":"武当派"
                        ]),

                (["id":"fanlao-huantong",
                        "tname":"返老还童功",
                        "rate":38,
                        "fam":"灵鹫宫"
                        ]),
                (["id":"taishang-wangqing",
                        "tname":"太上忘情",
                        "rate":38,
                        "fam":"古墓派"
                        ]),
                (["id":"xiaoyao-you",
                        "tname":"逍遥游",
                        "rate":37,
                        "fam":"逍遥派"
                        ]),
                (["id":"qimen-xuanshu",
                        "tname":"奇门玄术",
                        "rate":32,
                        "fam":"桃花岛"
                        ]),
                (["id":"xueying-dafa",
                        "tname":"血影大法",
                        "rate":33,
                        "fam":"密宗"
                        ]),
                (["id":"mizong-zhenyan",
                        "tname":"密宗真言",
                        "rate":33,
                        "fam":"密宗"
                        ]),
                (["id":"bixue-danxin",
                        "tname":"碧血丹心",
                        "rate":32,
                        "fam":"丐帮"
                        ]),
                (["id":"daojian-xiaotianwai",
                        "tname":"刀剑啸天外",
                        "rate":31,
                        "fam":"关外胡家"
                        ]),
                (["id":"lunhui",
                        "tname":"轮回",
                        "rate":31,
                        "fam":"少林派"
                        ]),
                (["id":"huitong-tianxia",
                        "tname":"慧通天下",
                        "rate":31,
                        "fam":"慕容世家"
                        ]),
                (["id":"guangming-jing",
                        "tname":"大云光明经",
                        "rate":37,
                        "fam":"明教"
                        ]),
                (["id":"jinchan-tunyue",
                        "tname":"金蟾吞月",
                        "rate":37,
                        "fam":"欧阳世家"
                        ]),
                (["id":"qimai-liuzhuan",
                        "tname":"气脉流转",
                        "rate":37,
                        "fam":"段氏皇族"
                        ]),
                (["id":"motun-tianxia",
                        "tname":"魔吞天下",
                        "rate":35,
                        "fam":"魔教"
                        ]),
                (["id":"luoxian-jue",
                        "tname":"落仙诀",
                        "rate":30,
                        "fam":"唐门世家"
                        ]),
                (["id":"richu-dongfang",
                        "tname":"日出东方",
                        "rate":34,
                        "fam":"日月神教"
                        ]),
                (["id":"xuantian-zhi",
                        "tname":"玄天无情指",
                        "rate":28
                        ]),
                (["id":"jiuyin-baiguzhao",
                        "tname":"九阴白骨爪",
                        "rate":31
                        ]),
                (["id":"shexing-lifan",
                        "tname":"蛇行狸翻",
                        "rate":40
                        ]),
                (["id":"luohan-fumogong",
                        "tname":"罗汉伏魔神功",
                        "rate":50
                        ]),
                (["id":"wuming-jianfa",
                        "tname":"无名剑法",
                        "rate":62
                        ]),
                (["id":"zhuangzi-wu",
                        "tname":"庄子舞",
                        "rate":72
                        ]),
                (["id":"shenxing-baibian",
                        "tname":"神行百变",
                        "rate":72
                        ]),
                (["id":"huhe-quan",
                        "tname":"虎鹤双形拳",
                        "rate":150
                        ]),
                (["id":"juedao",
                        "tname":"绝刀",
                        "rate":300
                        ]),
                (["id":"mieshenquan",
                        "tname":"灭神拳",
                        "rate":300
                        ]),
                (["id":"tianjian",
                        "tname":"天剑",
                        "rate":300
                        ]),
                (["id":"yinlong-bian",
                        "tname":"银龙鞭法",
                        "rate":100
                        ]),
                (["id":"liumang-shenquan",
                        "tname":"流氓神拳",
                        "rate":100
                        ]),
                (["id":"youming-zhi",
                        "tname":"幽冥指",
                        "rate":100
                        ]),
                (["id":"zhongping-qiang",
                        "tname":"中平枪法",
                        "rate":100
                        ]),
                (["id":"tianzhu-fuzhi",
                        "tname":"天竺拂指",
                        "rate":100
                        ]),
                (["id":"qilian-zhi",
                        "tname":"祁连五绝指",
                        "rate":100
                        ]),
                (["id":"changge-jian",
                        "tname":"长歌剑法",
                        "rate":72
                        ]),
                (["id":"sanshou",
                        "tname":"岳家散手",
                        "rate":190
                        ]),
                (["id":"kuangfeng-blade",
                        "tname":"狂风刀法",
                        "rate":130
                        ]),
                (["id":"tangshi-jian",
                        "tname":"唐诗剑法",
                        "rate":100
                        ]),
                (["id":"zhanshen-xinjing",
                        "tname":"战神心经",
                        "rate":250
                        ]),
                (["id":"xiaoyaobu",
                        "tname":"逍遥步",
                        "rate":100
                        ]),
                (["id":"zhanshenjue",
                        "tname":"战神诀",
                        "rate":100
                        ]),
                (["id":"yijin-duangu",
                        "tname":"易筋锻骨",
                        "rate":100
                        ]),
                (["id":"baihua-cuoquan",
                        "tname":"百花错拳",
                        "rate":250
                        ]),
                (["id":"banruo-zhang",
                        "tname":"般若掌",
                        "rate":400
                        ]),
                (["id":"changquan",
                        "tname":"太祖长拳",
                        "rate":400
                        ]),
                (["id":"cibei-dao",
                        "tname":"慈悲刀",
                        "rate":400
                        ]),
                (["id":"cuixin-zhang",
                        "tname":"摧心掌",
                        "rate":110
                        ]),
                (["id":"danding-dao",
                        "tname":"丹碇刀法",
                        "rate":100
                        ]),
                (["id":"ding-dodge",
                        "tname":"丁字步",
                        "rate":100
                        ]),
                (["id":"ding-force",
                        "tname":"小丁气功",
                        "rate":100
                        ]),
                (["id":"ding-unarmed",
                        "tname":"一横一勾拳",
                        "rate":100
                        ]),
                (["id":"duoluoye-zhi",
                        "tname":"多罗叶指",
                        "rate":400
                        ]),
                (["id":"fengyun-bianhuan",
                        "tname":"风云变幻",
                        "rate":100
                        ]),
                (["id":"fengyun-shou",
                        "tname":"风云手",
                        "rate":400
                        ]),
                (["id":"fumo-jian",
                        "tname":"伏魔剑",
                        "rate":400
                        ]),
                (["id":"guoshi-xinfa",
                        "tname":"郭氏心法",
                        "rate":150
                        ]),
                (["id":"guzhuo-zhang",
                        "tname":"古拙掌法",
                        "rate":100
                        ]),
                (["id":"hanmei-jian",
                        "tname":"寒梅剑法",
                        "rate":100
                        ]),
                (["id":"houquan",
                        "tname":"猴拳",
                        "rate":200
                        ]),
                (["id":"jingang-quan",
                        "tname":"大金刚拳",
                        "rate":500,
                        "no_learn_pfm":1
                        ]),
                (["id":"jinshe-jian",
                        "tname":"金蛇剑法",
                        "rate":120
                        ]),
                (["id":"jinshe-zhang",
                        "tname":"金蛇游身掌",
                        "rate":120
                        ]),
                (["id":"jinshe-zhui",
                        "tname":"金蛇锥法",
                        "rate":110
                        ]),
                (["id":"jinwu-blade",
                        "tname":"金乌刀法",
                        "rate":100
                        ]),
                (["id":"jinyan-gong",
                        "tname":"金雁功",
                        "rate":150
                        ]),
                (["id":"lansha-shou",
                        "tname":"蓝砂手",
                        "rate":100
                        ]),
                (["id":"liushui-bian",
                        "tname":"流水鞭法",
                        "rate":100
                        ]),
                (["id":"longzhua-gong",
                        "tname":"龙爪功",
                        "rate":400
                        ]),
                (["id":"luohan-quan",
                        "tname":"罗汉拳",
                        "rate":400
                        ]),
                (["id":"nianhua-zhi",
                        "tname":"拈花指",
                        "rate":400
                        ]),
                (["id":"piaoxu-zhang",
                        "tname":"飘絮掌法",
                        "rate":100
                        ]),
                (["id":"pili-daofa",
                        "tname":"霹雳刀法",
                        "rate":85
                        ]),
                (["id":"poyang-jian",
                        "tname":"破阳冷光剑",
                        "rate":100
                        ]),
                (["id":"poyue-zhao",
                        "tname":"破岳神爪",
                        "rate":100
                        ]),
                (["id":"pudu-zhang",
                        "tname":"普渡杖",
                        "rate":400
                        ]),
                (["id":"qianye-shou",
                        "tname":"如来千叶手",
                        "rate":400
                        ]),
                (["id":"qingmang-zhang",
                        "tname":"青莽掌",
                        "rate":120
                        ]),
                (["id":"qiufeng-chenfa",
                        "tname":"秋风拂尘",
                        "rate":150
                        ]),
                (["id":"qixing-zhi",
                        "tname":"七星指",
                        "rate":100
                        ]),
                (["id":"sanhua-zhang",
                        "tname":"散花掌",
                        "rate":400
                        ]),
                (["id":"tianhuan-shenjue",
                        "tname":"天寰神诀",
                        "rate":100
                        ]),
                (["id":"weituo-gun",
                        "tname":"韦驮棍",
                        "rate":400
                        ]),
                (["id":"wuchang-zhang",
                        "tname":"无常杖",
                        "rate":400
                        ]),
                (["id":"wuhu-duanmendao",
                        "tname":"五虎断门刀",
                        "rate":100
                        ]),
                (["id":"wushen-jian",
                        "tname":"衡山五神剑",
                        "rate":60
                        ]),
                (["id":"wuwang-shengong",
                        "tname":"无妄神功",
                        "rate":100
                        ]),
                (["id":"wuxiang-zhi",
                        "tname":"无相指法",
                        "rate":400
                        ]),
                (["id":"xiaoyaoyou",
                        "tname":"逍遥游拳法",
                        "rate":100
                        ]),
                (["id":"xinghui-canlan",
                        "tname":"星辉灿烂",
                        "rate":100
                        ]),
                (["id":"xiuluo-dao",
                        "tname":"修罗刀",
                        "rate":100
                        ]),
                (["id":"xiuluo-zhi",
                        "tname":"修罗指",
                        "rate":400
                        ]),
                (["id":"xuwu-piaomiao",
                        "tname":"虚无缥缈",
                        "rate":100
                        ]),
                (["id":"yijinjing",
                        "tname":"易筋经神功",
                        "rate":100
                        ]),
                (["id":"yingzhua-gong",
                        "tname":"鹰爪功",
                        "rate":100
                        ]),
                (["id":"yipai-liangsan",
                        "tname":"一拍两散",
                        "rate":200,
                        "no_learn_pfm":1
                        ]),
                (["id":"yizhi-chan",
                        "tname":"一指禅",
                        "rate":400,
                        "no_learn_pfm":1
                        ]),
                (["id":"yuanshi-jian",
                        "tname":"原始剑法",
                        "rate":100
                        ]),
                (["id":"yunhe-jian",
                        "tname":"云鹤七剑",
                        "rate":100
                        ]),
                (["id":"yunlong-bian",
                        "tname":"云龙鞭法",
                        "rate":200
                        ]),
                (["id":"yunlong-jian",
                        "tname":"云龙剑",
                        "rate":200
                        ]),
                (["id":"yunlong-shenfa",
                        "tname":"云龙身法",
                        "rate":200
                        ]),
                (["id":"yunlong-shengong",
                        "tname":"云龙神功",
                        "rate":200
                        ]),
                (["id":"yunlong-shou",
                        "tname":"云龙手",
                        "rate":200
                        ]),
                (["id":"yunlong-zhua",
                        "tname":"云龙爪",
                        "rate":200
                        ]),
                (["id":"zhenyu-quan",
                        "tname":"镇狱拳法",
                        "rate":105
                        ]),
                (["id":"zui-gun",
                        "tname":"少林醉棍",
                        "rate":400,
                        "no_learn_pfm":1
                        ]),
                (["id":"zui-quan",
                        "tname":"醉拳三打",
                        "rate":400,
                        "no_learn_pfm":1
                        ]),
                (["id":"certosina",
                        "tname":"镶嵌技艺",
                        "rate":101
                        ]),
                (["id":"yunlong-xinfa",
                        "tname":"云龙心法",
                        "rate":200
                        ]),
                (["id":"driving",
                        "tname":"赶车技巧",
                        "rate":165
                        ]),
                (["id":"count",
                        "tname":"阴阳八卦",
                        "rate":15
                        ]),
                (["id":"jingluo-xue",
                        "tname":"经络学",
                        "rate":111
                        ]),
                (["id":"mathematics",
                        "tname":"算术",
                        "rate":111
                        ]),
                (["id":"riding",
                        "tname":"骑术",
                        "rate":111
                        ]),
                (["id":"sanscrit",
                        "tname":"梵文",
                        "rate":111
                        ]),
                (["id":"training",
                        "tname":"驭兽术",
                        "rate":111
                        ]),
                (["id":"array",
                        "tname":"阵法",
                        "rate":600
                        ]),
                (["id":"buddhism",
                        "tname":"禅宗心法",
                        "rate":265
                        ]),
                (["id":"chuancai-jiyi",
                        "tname":"川菜技艺",
                        "rate":150
                        ]),
                (["id":"higgling",
                        "tname":"还价技巧",
                        "rate":101
                        ]),
                (["id":"idle-force",
                        "tname":"发呆神功",
                        "rate":111
                        ]),
                (["id":"lamaism",
                        "tname":"密宗心法",
                        "rate":265
                        ]),
                (["id":"liandan-shu",
                        "tname":"炼丹术",
                        "rate":600
                        ]),
                (["id":"stealing",
                        "tname":"妙手空空",
                        "rate":95
                        ]),
                (["id":"taoism",
                        "tname":"道学心法",
                        "rate":265
                        ]),
                (["id":"mahayana",
                        "tname":"大乘涅磐功",
                        "rate":295
                        ]),
                (["id":"chess",
                        "tname":"弈棋之道",
                        "rate":115
                        ]),
                (["id":"drawing",
                        "tname":"绘画技巧",
                        "rate":115
                        ]),
                (["id":"enchanting",
                        "tname":"附魔技艺",
                        "rate":165
                        ]),
                (["id":"acupuncture",
                        "tname":"针灸之术",
                        "rate":200
                        ]),
                (["id":"gleaning",
                        "tname":"捡大粪",
                        "rate":200
                        ]),
                (["id":"chinese-anthem",
                        "tname":"义勇军进行曲",
                        "rate":20
                        ]),
                (["id":"literate",
                        "tname":"读书写字",
                        "rate":1500
                        ]),
        });


void create()
{
        set_name(NOR BRED YEL "『" NOR BRED HIY "万象天书" NOR BRED YEL "』" NOR, ({"wanxiang book", "book"}));
        set_weight(5);
                set("unit", "本");
                set("value", 1);
                set("weight", 5);
                set("material", "paper");
                set("longx", "这是本玄奥无比的书籍，化身千万，可以打开(open book)试试。\n");
                set("set_data", 1); 
                set("auto_load", 1); 
                set("no_sell", 1);
                set("no_pawn", 1);        
                //set("no_steal", 1);
                //set("no_beg", 1);
                setup();
        if (query("opened")) {
                set_name(query("opened/name"), ({ query("opened/skill") + " book", "wanxiang book", "book"}));
                switch(query("opened/type")) {
                        case 1:
                                set("longx", "这是一本武学补遗，你(read)后可以学会「"+query("opened/can_perform")+"」的使用诀窍。\n");
                                break;
                        case 2:
                                set("longx", "这是一本武学秘笈，你(read)后可以提高『"+query("opened/tname")+"』的修为。\n");
                                break;
                        case 3:
                                set("longx", "这是一本技能秘籍，你(read)后可以提高『"+query("opened/tname")+"』的知识。\n");
                                break;
                }
        }
}        

string long()
{
        return query("longx");
}

int do_open(string arg)
{
        int i, k, rate, *rates = ({}), totalrate = 0, rndrate;
        string oldname, pfmpath, *pfmfs = ({}), rndpfm, *tname = ({}), *skid = ({});
        mixed *pfmfiles;
        mapping b;
        object me = this_player();
        
        if (!arg || (arg!=query("id") && arg!="book")) return 0;
        
        if (!query("no_open_msg") && me && playerp(me) && wiz_level(me) < 5) {
                if (me->is_busy() || me->is_fighting())
                        return notify_fail(NOR BUSY_MESSAGE NOR);
                me->start_busy(1);
        }

        if (query("opened")) return notify_fail(NOR "这本书已经打开了啊，好好研究(look)它吧。\n" NOR);

        oldname = query("name");
        
        for(i=0; i<sizeof(booklists); i++) {
                rate = booklists[i]["rate"];
                totalrate += rate;
                rates += ({rate});
                tname += ({booklists[i]["tname"]});
                skid += ({booklists[i]["id"]});
        }
        
        rndrate = random(totalrate);
        totalrate = 0;
        
        for(i=0; i<sizeof(rates); i++) {
                //write("totalrate:" + (string)totalrate + "\n");
                if (rndrate >= totalrate && rndrate < (totalrate + rates[i])) {
                        set("opened/skill", skid[i]);
                        set("opened/tname", tname[i]);
                        if (booklists[i]["fam"]) set("opened/fam", booklists[i]["fam"]);
                        if ( (string) SKILL_D(skid[i])->type() == "martial" ) {
                                if (!booklists[i]["no_learn_pfm"]) {
                                        pfmpath = "/kungfu/skill/" + skid[i] + "/";
                                        if (SKILL_D(skid[i])->valid_enable("force")) pfmpath += "perform/";
                                }
                                if (pfmpath && file_size(pfmpath) == -2) {
                                        pfmfiles = get_dir(pfmpath, -1);
                                        if (pfmfiles && sizeof(pfmfiles)) {
                                for (k = 0; k < sizeof(pfmfiles); k++)
                                {
                                        if (pfmfiles[k][0][strlen(pfmfiles[k][0])-2..strlen(pfmfiles[k][0])] != ".c")
                                                                                     continue;
                                        pfmfs += ({replace_string(pfmfiles[k][0], ".c", "")});
                                }
                                                if (pfmfs && sizeof(pfmfs)) rndpfm = pfmfs[random(sizeof(pfmfs))];
                                        }
                                }
                                if (random(25)==0 && rndpfm) {//极小几率，并且随机至少有一个pfm的情况下
                                        set("opened/name", NOR+YEL+"『"+YEL+tname[i]+NOR+YEL+"·"+YEL+"补遗"+NOR+YEL+"』"+NOR);
                                        set("longx", "这是一本武学补遗，你(read)后可以学会「"+rndpfm+"」的使用诀窍。\n");
                                        set("opened/type", 1);
                                        set("opened/can_perform", rndpfm);
                                } else {
                                        set("opened/name", NOR+YEL+"『"+WHT+tname[i]+NOR+YEL+"·"+WHT+"秘笈"+NOR+YEL+"』"+NOR);
                                        set("longx", "这是一本武学秘笈，你(read)后可以提高『"+tname[i]+"』的修为。\n");
                                        set("opened/type", 2);
                                }
                        } else {
                                set("opened/name", NOR+YEL+"『"+CYN+tname[i]+NOR+YEL+"·"+CYN+"秘籍"+NOR+YEL+"』"+NOR);
                                set("longx", "这是一本技能秘籍，你(read)后可以提高『"+tname[i]+"』的知识。\n");
                                set("opened/type", 3);
                        }
                        //write(HIY + "rndrate:" + (string)rndrate + "<" + (string)(totalrate + rates[i]) + "\n" + NOR);
                        break;
                }
                totalrate += rates[i];
        }
        //write(HIC + tname[i] + ":" + (string)rates[i] + "\n" + NOR);//小于100为值得报道的珍惜品
        set_name(query("opened/name"), ({ skid[i] + " book", "wanxiang book", "book"}));
        if (!query("no_open_msg")) message_vision(NOR + CYN + "$N" + NOR + CYN + "打开"+ oldname + NOR + CYN + "获得了一本" +query("name") + NOR + CYN + "。\n" + NOR, me);
        if (rates[i]<20 && me && objectp(me) && playerp(me)) {
                log_file("static/wanxiangbook", (string)ctime(time()) + ": " + query("name", me) + "(" + query("id", me) + ") " + "->" + query("name") + "-" + skid[i] + "\n");
        }
        return rates[i];
}

int do_read(string arg)
{
        object me = this_player();
        string sks, pfm;
        int flagused = 0, diff, improve = 3000000;
        int pot = 100000;
                
        if (!arg || (arg!=query("id") && arg!="book")) return 0;

        if (me && playerp(me) && wiz_level(me) < 5) {
                if (me->is_busy() || me->is_fighting())
                        return notify_fail(NOR BUSY_MESSAGE NOR);
                me->start_busy(1);
        }
        
        if (!query("opened")) return notify_fail(NOR "这可是万象天书啊，打开(open)再研读吧。\n" NOR);
        
        if ( query("opened/type") == 1 && ( (query("potential", me)-query("learned_points", me))<100000000 ) )
                return notify_fail(NOR "从万象天书上学习绝技需要１亿点潜能。\n" NOR);
        else if ( query("opened/type") == 2 && ( (query("potential", me)-query("learned_points", me))<1000000 ) )
                return notify_fail(NOR "阅读万象天书学习武功至少需要１００万点潜能。\n" NOR);
        else if ( (query("potential", me)-query("learned_points", me))<1000 )
                return notify_fail(NOR "阅读万象天书学习知识至少需要１０００点潜能。\n" NOR);
        
        sks = query("opened/skill");
        
        improve *= (query("int",me) / 5) + 12;//已测试，先天40int的id要达到150level，没有diff的也需要吃12本
                switch(query("opened/type")) {
                        case 1:
                                pfm = query("opened/can_perform");
                                if ( me->query_skillo(sks, 1)>149 ) {
                                        set("can_perform/" + sks + "/" + pfm, 1, me);
                                        tell_object(me, NOR + "你冥思苦想，终于从万象天书上习得了「"+pfm+"」的绝技。\n" + NOR);
                                        addn("potential", -100000000, me);
                                        flagused = 1;
                                } else {
                                        tell_object(me, NOR + "你还不会「"+query("opened/tname")+"」或者低于１５０级。 \n" + NOR);
                                }
                                break;
                        case 2:
                                        diff = SKILLS_D->query_skill_difficult(sks); 
                                        if (! diff) diff = SKILL_D(sks)->difficult_level(); 
                                        improve = improve / (300 + diff); 
                                        if (improve < 500) improve = 500; 
                                        if (!me->can_improve_skill(sks)) {
                                                write(NOR + "也许是缺乏实战经验，你感到难以继续研究「" + query("opened/tname") + "」的问题了。\n" + NOR); 
                                        } else if (query("opened/fam") && query("opened/fam")!=query("family/family_name", me)) {
                                                write(NOR + "只有" + query("opened/fam") + "的弟子才能研究「" + query("opened/tname") + "」。\n" + NOR); 
                                        } else {
                                                me->improve_skill(sks, improve); 
                                                write(NOR "你研究了一会，似乎对「"+query("opened/tname")+"」有些新的领悟。\n" + NOR); 
                                        addn("potential", -1000000, me);
                                                flagused = 1;
                                        }
                                break;
                        case 3:
                                if (query("opened/fam") && query("opened/fam")!=query("family/family_name", me)) {
                                                write(NOR + "只有" + query("opened/fam") + "的弟子才能学习「" + query("opened/tname") + "」。\n" + NOR); 
                                        } else if ( me->query_skillo(sks, 1)<5000 || sks=="literate" ) {
                                                me->improve_skill(sks, improve / 800); 
                                                write(NOR "你研究了一会，似乎对「"+query("opened/tname")+"」有些新的领悟。\n" + NOR); 
                                        addn("potential", -1000, me);
                                                flagused = 1;
                                } else {
                                        tell_object(me, NOR + "你的「"+query("opened/tname")+"」超过了５０００级，已经无法再从万象天书上学习了。 \n" + NOR);
                                }
                                break;
                }
    if (flagused) {
        message_vision(NOR + CYN + "$N" + NOR + CYN + "手里的" +query("name") + NOR + CYN + "一振化为飞灰。\n" + NOR, me);             
        destruct(this_object());
    }
        return 1;
}

int do_setsk(string arg)
{
        if (!arg) return notify_fail(NOR "要测试什么skill？\n" NOR);
        set("opened/skill", arg);
        set("opened/tname", arg);
        set("opened/type", 2);
        set("longx", "这是一本测试用的武学秘笈，(read book)\n");
        set_name("测试秘笈", ({"book"}));
        write("ok\n");
        return 1;
}

void init()
{
        add_action("do_open", "open");
        add_action("do_read", "read");
        if (wiz_level(this_player()) > 5) 
                add_action("do_setsk", "setsk");
}


