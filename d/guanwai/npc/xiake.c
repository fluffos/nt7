#include <ansi.h>
int do_copy(object me);
int do_back(object me);
inherit NPC;
string* names = ({
"赵","钱","孙","李","周","吴","郑","王","冯","陈","褚","卫",
"蒋","沈","韩","杨","朱","秦","尤","许","何","吕","施","张",
"孔","曹","严","华","金","魏","陶","姜","戚","谢","邹","喻",
"柏","水","窦","章","云","苏","潘","葛","奚","范","彭","郎",
"鲁","韦","昌","马","苗","凤","花","方","傻","任","袁","柳",
"邓","鲍","史","唐","费","廉","岑","薛","雷","贺","倪","汤",
"藤","殷","罗","华","郝","邬","安","常","乐","呆","时","付",
"皮","卞","齐","康","伍","余","元","卜","顾","盈","平","黄",
"和","穆","肖","尹","姚","邵","湛","汪","祁","毛","禹","狄",
"米","贝","明","藏","计","伏","成","戴","谈","宋","茅","庞",
"熊","纪","舒","屈","项","祝","董","梁","樊","胡","凌","霍",
"虞","万","支","柯","昝","管","卢","英","仇","候","岳","帅",
"司马","上官","欧阳","夏候","诸葛","闻人","东方","赫连","皇甫",
"尉迟","公羊","澹台","公治","宗政","濮阳","淳于","单于","太叔",
"申屠","公孙","仲孙","辕轩","令狐","钟离","宇文","长孙","幕容",
"司徒","师空","颛孔","端木","巫马","公西","漆雕","乐正","壤驷",
"公良","拓趾","夹谷","宰父","谷梁","楚晋","阎法","汝鄢","涂钦",
"段千","百里","东郭","南郭","呼延","归海","羊舌","微生","梁丘",
"左丘","东门","西门","佰赏","南官",
"缑","亢","况","后","有","琴","商","牟","佘","耳","墨","哈",
"谯","年","爱","阳","佟","第","五","言","福","蒯","钟","宗",
"林","石",
});

string* ids = ({
"zhao","qian","sun","li","zhou","wu","zhen","wang","feng","chen","zhu","wei",
"jiang","shen","han","yang","zhu","qing","you","xu","he","lu","shi","zhang",
"kong","cao","yan","hua","jin","wei","tao","jiang","qie","xie","zhou","yu",
"bo","shui","dou","zhang","yun","su","pan","ge","xi","fan","peng","lang",
"lu","wei","chang","ma","miao","feng","hua","fang","sha","ren","yuan","liu",
"deng","bao","shi","tang","fei","lian","chen","xue","lei","he","ni","tang",
"teng","yin","luo","hua","hao","wu","an","chang","le","dai","shi","fu",
"pi","bian","qi","kang","wu","yu","yuan","po","gu","ying","ping","huang",
"he","mu","xiao","yin","yao","shao","zhan","wang","qi","mao","yu","di",
"mi","bei","ming","zang","ji","fu","cheng","dai","tan","song","mao","pang",
"xiong","ji","su","qu","xiang","zhu","dong","liang","fan","hu","ling","ho",
"yu","wan","zhi","ke","jiu","guan","lu","ying","qiu","hou","yue","suai",
"sima","shangguan","ouyang","xiahou","zhuge","wenren","dongfang","helian","huangpu",
"weichi","gongyang","zhantai","gongye","zongzheng","puyang","chunyu","shanyu","taishu",
"shentu","gongshun","zhongshun","xuanyuan","linghu","zhongli","yuwen","changshun","murong",
"situ","shikong","zhuankong","duanmu","wuma","gongxi","qidiao","lezheng","xiangsi",
"gongliang","tuozhi","jiagu","zaifu","guliang","chujing","yanfa","ruye","tuqin",
"duanqian","baili","dongguo","nanguo","huyan","guihai","yangshe","weisheng","liangqiu",
"zuoqiu","dongmen","ximen","baishang","nangong",
"gou","kang","kuang","hou","you","qing","shang","mo","she","er","mo","ha",
"qiao","nian","ai","yang","dong","di","wu","yan","fu","kai","zong","zong",
"lin","shi",
});
//----以下欢迎添加，nm2需要一定的空字，以便产生出单名--------------
string* nm2 = ({
"忠","孝","礼","义","智","勇","仁","匡","宪","令","福","禄","大","小","晓",
"高","可","阿","金","世","克","叔","之","公","夫","时","若","庆","文","武",
"多","才","长","子","永","友","自","人","为","铁","","","","","","","","",
"","","","","","","","","","","","","","",
});

string* nm3 = ({
"霸","白","班","斌","宾","昌","超","诚","川","鼎","定","斗",
"法","飞","风","锋","钢","罡","贯","光","海","虎","华",
"浩","宏","济","坚","健","剑","江","进","杰","俊","康",
"良","麟","民","明","鸣","宁","培","启","强","荣","山",
"泰","涛","挺","伟","熙","祥","雄","旭",
"毅","瑜","羽","宇","岳","舟",
});

#include <ansi.h>
void away();

void create()
{
   string weapon;
   int i = random(sizeof(names));
  set_name(names[i]+nm2[random(sizeof(nm2))]+nm3[random(sizeof(nm3))], ({"qingbing"}));
        set("nickname", HIG"大清官兵"NOR);
        set("gender", "男性");
        set("age", 22);
        set("long", 
                "他是一个大清官兵。\n");
        set("attitude", "peaceful");
        set("age", random(10) + 25);
        set("no_quest", 1);
        set("str", 33);
        set("con", 26);
        set("int", 20);
        set("dex", 23);
        set("combat_exp", 1080000 + random(4000000)); 
        set("attitude", "friendly");
        set_skill("force", 50);
        set_skill("sword", 50);
        set_skill("dodge", 50);
        set_skill("parry", 50);
     set_skill("jiuyang-shengong", 100);
    set_skill("qiankun-danuoyi", 100);
    set_skill("qishang-quan", 100);
    set_skill("shenghuo-shengong", 100);
    set_skill("taiji-quan",150);
    set_skill("taiji-jian",150);
    set_skill("taiji-dao",150);
    set_skill("shenghuo-ling",300);

    map_skill("force", "shenghuo-shengong");
    map_skill("dodge", "qiankun-danuoyi");
    map_skill("unarmed", "qishang-quan");
    map_skill("cuff", "qishang-quan");
    map_skill("hand", "taiji-quan");
    map_skill("sword","shenghuo-ling");
    map_skill("parry","shenghuo-ling");
    map_skill("blade","taiji-dao");
        set("max_qi", 1450); 
        set("eff_jingli", 1400); 
        set("neili", 1700); 
        set("max_neili", 1700);
        set("jiali", 30);
        set("chat_chance_combat", 30);
        set("chat_msg_combat", ({
                (: perform_action, "sword.can" :),
                (: perform_action, "sword.lian" :),
                (: perform_action, "sword.xi" :),
                (: perform_action, "sword.hua" :),                
                (: command("unwield jian") :),
                (: command("unwield jian") :),
                (: command("wield jian") :),
                (: command("wield jian") :),
                (: perform_action, "cuff.fei" :),                
                (: perform_action, "cuff.shang" :),                
                (: perform_action, "cuff.fei" :),                
                (: perform_action, "cuff.shang" :),                
                (: perform_action, "dodge.yi" :),                                
                (: perform_action, "dodge.yi" :),                                
        }) );
        weapon = "/clone/weapon/gangjian";
        setup();
        carry_object(weapon)->wield();
        carry_object("/clone/cloth/cloth")->wear();
        add_money("silver", 50);
}

int do_back(object me)
{
        destruct(me);
        return 1;
}

int checking(object ob, object me)
{
        if(!me || !present(me, environment())) do_back(ob);
        else call_out("checking", 2, ob, me);
        return 1;
}

int do_copy(object me)
{
        int i;
        object ob;
        ob = this_object();

      if( !query_temp("xx_rob", me)){
                 do_back(me);
                 return 0;
                 }
        message_vision(HIR"突然从附近窜出一个$N，二话不说就扑向了$n！\n"NOR, ob, me);
        addn_temp("biaoshi", 1, me);
        
        set("combat_exp",query("combat_exp",  me)*4/5, ob);
        set("max_qi",query("max_qi",  me), ob);
        set("eff_qi",query("max_qi",  me), ob);
        set("qi",query("max_qi",  me), ob);
        set("max_jingli",query("max_jingli",  me), ob);
        set("eff_jingli",query("max_jingli",  me), ob);
        set("jingli",query("max_jingli",  me), ob);
        set("max_neili",query("max_neili",  me), ob);
        set("neili",query("max_neili",  me), ob);
        ob->set_skill("force", me->query_skill("force"));
        ob->set_skill("jiuyang-shengong", me->query_skill("force")* 4 / 5);
        ob->set_skill("qiankun-danuoyi", me->query_skill("force")* 4 / 5);
        ob->set_skill("qishang-quan", me->query_skill("force")* 4 / 5);
        ob->set_skill("shenghuo-shengong",me->query_skill("force")* 4 / 5);
        ob->set_skill("dodge", me->query_skill("force")* 4 / 5); 
        ob->set_skill("sword", me->query_skill("force")* 4 / 5); 
        ob->set_skill("taiji-quan", me->query_skill("force")* 4 / 5); 
        ob->set_skill("parry",me->query_skill("force")* 4 / 5); 
        ob->set_skill("shenghuo-ling", me->query_skill("force")* 4 / 5);
        set("shen", -1000, ob);
        ob->kill_ob(me);
        me->kill_ob(ob);
        checking(ob, me);    
        call_out("do_back", 350,  ob);  
        return 1;
}
