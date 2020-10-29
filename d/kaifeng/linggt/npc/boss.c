// This program is a part of NITAN MudLIB 
// redl 2012/12/1 
#include <ansi.h>
inherit NPC;



//奖励频道
#define CHANL_NAME "sys"

#define GIFT_EXP 68000  //赏经验，依照等级差来放大，战力越强越级挑战时获益越多

#define N_INCREASE 25

#define HP_QI_BASE 1000000                      //气的基础值
#define HP_QI_INCREASE 0.01                     //每提升1层的精和气增加比例（N_INCREASE层一个阶段）
#define HP_QI_XINCREASE 2.0                     //除非断绝do 20 pfm方可改回1.9                  //每N_INCREASE层改变气的指数
#define HP_JING_PERCENT 1.5                     //精和气的比例
#define HP_NEILI_PERCENT 0.15            //内力和气的比例

#define SK_BASE 800                                     //基础
#define SK_LV 500        //原作480                                       //变数
#define SK_INCREASE 0.005                       //比例
#define SK_XINCREASE 1.4                        //指数


int nflee = 900;

string *warning_desc = ({
        HIG + "毫不费力" + NOR, HIG + "轻松搞定" + NOR, HIG + "一战可定" + NOR, HIY + "有点意思" + NOR, HIY + "棋逢对手" + NOR, 
        HIY + "需要警慎" + NOR, HIY + "有点够呛" + NOR, HIR + "难以取胜" + NOR, HIR + "极度危险" + NOR, HIR + "纯属自杀" + NOR, 
});

int ttype() 
{
        if (!environment() || !objectp(environment())) return 0;
        return environment()->tower_type();
}

int invert_reborngiftd(object me, int exp)
{
        if (query("reborn/times", me)) exp *= 2;//抵消转世的奖励惩罚
        return exp;
}

int get_show_giftexp(object me, int exp)//在news频道用来显示的经验奖励值
{
        int quest_times;
        if (MEMBER_D->is_double_reward(me)) exp *= 2;
        quest_times = "/adm/daemons/actiond"->query_action("quest_reward");
        if (quest_times) exp *= quest_times;
        if( me->query_bunch() && BUNCH_D->query_bunch_efficient(me->query_bunch(), "exp") ) exp *= 2;        
        if( me->query_family() && FAMILY_D->query_family_efficient(me->query_family(), "exp") ) exp *= 2;        
        return exp;
}

int is_boss() { return 1; }

void wield_wfile(string wfile)//提前装备
{
        object weapon; 
        weapon = new(wfile);
        weapon->move(this_object()); 
        weapon->wield(); 
        set("chance_summon", -1);//如果掉落毁坏，故意不再有机会装备了!
}

void check_weapon()
{
        object me,weapon; 
        string str, wname;

        me = this_object();
        if (!objectp(me)) return;
        wname = query("weaponname");
        if (!wname) return;
        
        if (!query_temp("weapon"))
        {
                if (objectp(query_last_damage_from())) query_last_damage_from()->start_busy(3+random(3));//给点时间我带武器，不论对方有多少pfm busy
                weapon = new(wname);
                weapon->move(this_object()); 
                str = sprintf("%s" HIY "虚空一抓，突然%s" HIY "出现在他的手中。\n" NOR,
                                       query("name", me),
                                       query("name", weapon));
                        tell_room(environment(me), str, me);
                weapon->wield(); 
        }
        return;
}

int hand_throw()
{
        object ob, me = this_object();
        
        if (!query("hand_throwing")) return 1;
        if (me->is_busy()) return 1;
        if (query_temp("handing")) return 1;

        ob = new(query("hand_throwing"));
        if( ob->query_amount() ) {
                ob->set_amount(999);
        }
        
        ob->move(me);
        command("hand " + query("id", ob));
        return 1;
}

void heart_beat()
{
                int cs, i;
                
                nflee --;
                if (!nflee) {
                        destruct(this_object());
                        return;
                }
                
        // 解除不能perform yun的限制
        if (!random(5))
        {
                this_object()->clear_condition("no_perform");
                this_object()->clear_condition("no_exert");
                delete_temp("no_perform");
                delete_temp("no_exert");
                if (!random(2))
                        this_object()->stop_busy();
        }
                
                if (!random(5) && objectp(query_last_damage_from())) {  //20%换招，以免被玩家一直刷damage
                        query_last_damage_from()->start_busy(2+random(3));
                }
                
                cs = query("chance_summon");
                
                if (cs) if (cs > random(10)) {
                        check_weapon();
                }

                cs = query("chance_perform");
                
                if (cs) if (cs > random(100)) {
                        check_weapon();
                        if (this_object()->query_skill_mapped("blade") == "kuangfeng-blade") {
                        i = 21;//21刀
                        addn_temp("apply/attack", query("elv") * 3000);
                        while (i--) {this_object()->command("perform blade.kuang");this_object()->stop_busy();}
                        addn_temp("apply/attack", - query("elv") * 3000);
                    }
                        else if (this_object()->query_skill_mapped("sword") == "kuangfeng-jian") {
                        i = 14;//14剑
                        addn_temp("apply/attack", query("elv") * 6000);
                        while (i--) {this_object()->command("perform sword.yong");this_object()->stop_busy();}
                        addn_temp("apply/attack", - query("elv") * 6000);
                    }

                        
                }

                hand_throw();
                
                if (ttype()==2 && !random(4)) {
                        this_object()->stop_busy();
                }
                
        return ::heart_beat();
}


void do_presk(string fam, int nlv, string bhand,string shand,string sparry,string sdodge,string sforce,string weaponname,string bweapsk,string sweapsk,string strpfm1,string strpfm2,string strpfm3)
{
        string extstr, stmp = to_chinese(shand);
        int tlv = query("level"), elv = query("elv");

        //write("elv:" + to_string(elv) + "\n");
        
        if (nlv > 20000000) set("title", HIY + fam + "魔王" + NOR);
        else if (nlv > 2000000) set("title", HIY + fam + "邪魔" + NOR);
        else if (nlv > 200000) set("title", HIY + fam + "狂魔" + NOR);
        else if (nlv > 20000) set("title", HIY + fam + "恶魔" + NOR);
        else if (nlv > 10000) set("title", HIY + fam + "恶人" + NOR);
        else if (nlv > 5000) set("title", HIY + fam + "凶徒" + NOR);
        else set("title", HIY + fam + "逆徒" + NOR);
        
        if (sweapsk!="") stmp += "、" + to_chinese(sweapsk);
        if (sparry!=shand && sparry!=sweapsk) stmp += "、" + to_chinese(sparry);
        stmp += "、" + to_chinese(sdodge);
        stmp += "、" + to_chinese(sforce);

        set("wmsg", HIG + "据说上面关押的是：" + query("title") + HIG + "，擅长武功是：" + stmp + 
                "。\n    我觉得你对上他是" + warning_desc[elv] + HIG + "的。如果你还有灵符次数，现在就可以使用(pass)换掉他！\n" + HIG + NOR);

        set_skill(bhand, nlv);
        set_skill(shand, nlv);
        map_skill(bhand, shand);
        prepare_skill(bhand, shand); 
        
        set_skill("parry", nlv);
        set_skill(sparry, nlv);
        map_skill("parry", sparry);
                
        set_skill("dodge", nlv);
        set_skill(sdodge, nlv);
        map_skill("dodge", sdodge);

        set_skill("force", nlv);
        set_skill(sforce, nlv);
        map_skill("force", sforce);
        
        if (tlv > 950) {
                if (random(4)) {
                        set_skill("taoism", 10000);
                        if (bweapsk=="sword" && random(8)){
                                set_skill("baijin-jianqi", 2000 + random(80000));
                                map_skill("taoism", "baijin-jianqi");
                        } else if (bweapsk=="blade" && random(8)){
                                set_skill("xuanli-daogang", 2000 + random(80000));
                                map_skill("taoism", "xuanli-daogang");
                        } else {
                                set_skill("houtu-shengong", 4000 + random(60000));
                                map_skill("taoism", "houtu-shengong");
                        }
                }
        }

        if (weaponname!=""){
                if (!query("chance_summon")) set("chance_summon", 3);//默认
                set("weaponname", weaponname);
                set_skill(bweapsk, nlv);
                set_skill(sweapsk, nlv);
                map_skill(bweapsk, sweapsk);
        }

//      set_skill("douzhuan-xingyi", nlv);
//      set_skill("shenyuan-gong", nlv);
//      set_temp("murong/xingyi", 1);
        set_skill("leg", nlv);//青城
        set_skill("jingluo-xue", nlv / 2);
        set_skill("throwing", nlv);//星宿炼心弹、桃花岛、唐门等需要
        
        
        if (shand == "sad-strike"){
                set("family/family_name", "古墓派");
                set("couple/couple_id", "小龙女");
        }
        if (shand == "dragon-strike"){
                set("family/family_name", "丐帮");
                set_temp("yield", 1);
        }
        if (shand == "nuquan"){
                set("family/family_name", "魔教");
                set_skill("mojiao-medical", 1000);
                set_skill("motun-tianxia", random(900)+ 100);
                if (nlv > 20000){
                        set_skill("motun-tianxia", random(nlv / 10)+ 100);
                }
        }
        if (shand == "canhe-zhi"){
                set("family/family_name", "慕容世家");
                set_skill("shenyuan-gong", nlv);
                if (nlv > 20000){
                        set_temp("yixinghuanyue", 1);
                }
        }
        if (shand == "mingyu-gong"){
                set("gender", "女性");
        } else if (sweapsk=="yuenv-jian"){
                set("per", 9);
                set("gender", "女性");
        } else {
                set("gender", "男性");
        }
        if (shand == "tanzhi-shentong"){
                set("family/family_name", "桃花岛");
                set_skill("qimen-wuxing", nlv / 10);
                set_skill("qimen-xuanshu", nlv / 10);
                //这里添加hand暗器
                set("hand_throwing", "/d/chengdu/npc/obj/flower-leaf");
        }
        if (sweapsk=="lunhui-jian"){
                                        set_skill("buddhism", nlv / 10);
                        set_skill("lunhui", random(1400)+ 100);
                        if (nlv > 20000){
                           set_skill("lunhui", random(nlv / 10)+ 100);
                        }
        }
        if (fam == "白驼"){
                set("family/family_name", "欧阳世家");
                if (elv >= 7){
                        set_skill("jinchan-tunyue", random(1400)+ 100);
                        if (nlv > 20000){
                           set_skill("jinchan-tunyue", random(nlv / 10)+ 100);
                        }
                }
        }
                if (elv >= 5 && fam=="峨眉") {
                        set("family/family_name", "峨眉派");
                        set_skill("claw", nlv);
                        set_skill("jiuyin-baiguzhao", nlv);
                        map_skill("claw", "jiuyin-baiguzhao");
                        set_skill("finger", nlv);
                        set_skill("tiangang-zhi", nlv);
                        map_skill("finger", "tiangang-zhi");
                        set_skill("emei-jiuyang", nlv / 2);
                        
                        set_skill("mingyu-gong", nlv);
                        set_skill("daojian-guizhen", nlv);
                        set_skill("taiji-jian", nlv);
                        set_skill("kuihua-mogong", nlv);
                        set_skill("lonely-sword", nlv);
                        set_skill("huifeng-jian", nlv);
                        set_skill("lunhui-jian", nlv);
                        set_skill("pixie-jian", nlv);
                        set_skill("xuantie-jian", nlv);
                        set_skill("yuxiao-jianfa", nlv);
                        set_skill("shedao-qigong", nlv);
                        set_skill("force-cognize", nlv / 3);
                        
            set_skill("jingxin", random(700)+ 300);
            set_skill("mahayana", 600 + random(3000));
            set_skill("array", 300 + random(3000));
                if (nlv > 20000){
                        set_skill("jingxin", random(nlv / 18)+ 300);
                        set_skill("mahayana", random(nlv / 5));
                }
                }
        if (fam == "胡家"){
                set_skill("daojian-xiaotianwai", random(1400)+ 100);
                if (nlv > 20000){
                        set_skill("daojian-xiaotianwai", random(nlv / 10)+ 100);
                }
                if (sweapsk=="daojian-guizhen") {
                                        set_skill("sword", nlv); 
                                        map_skill("sword", sweapsk); 
                    //hand剑
                        set("hand_throwing", "/clone/weapon/sword");
                }
                set_skill("baisheng-daofa", nlv); 
                                set_skill("medical", random(nlv)+ 500); 
                                set_skill("yaowang-miaoshu", random(nlv)+ 500); 
                                map_skill("medical", "yaowang-miaoshu"); 
        }
        if (fam == "唐门"){
                                set_skill("tangmen-throwing", nlv);
                                map_skill("throwing", "tangmen-throwing");
                set_skill("luoxian-jue", random(1400)+ 100);
                if (nlv > 20000){
                        set_skill("luoxian-jue", random(nlv / 10)+ 100);
                }
                                set_skill("poison", random(700)+ 500); 
                                set_skill("medical", random(700)+ 500); 
                                set_skill("tangmen-poison", random(700)+ 500); 
                                set_skill("tangmen-medical", random(700)+ 500);         
                                map_skill("poison", "tangmen-poison"); 
                                map_skill("medical", "tangmen-medical"); 
                //这里添加hand暗器
                set("hand_throwing", "/kungfu/class/tangmen/obj/hua");
        }
        if (fam == "华山"){
                set_skill("jianyi", random(1400) + tlv);
        }
        if (shand == "chousui-zhang"){
                set("family/family_name", "星宿派");
                set_skill("huagong-dafa", nlv);
                set_skill("poison", random(700)+ 300);
                set_skill("xingxiu-qishu", random(700)+ 300);
                                map_skill("poison", "xingxiu-qishu"); 
                if (nlv > 20000){
                        set_skill("poison", random(nlv / 10)+ 300);
                }
        }
        if (shand == "jiuyin-baiguzhao" && sparry == "qiankun-danuoyi"){
                if (nlv > 20000) set_temp("nuozhuan", 1);
        }
        if (shand == "taiji-quan"){
                set_skill("taoism", random(1200)+ 300);
                set("shen", 8000000 + nlv * 200);
                if (nlv > 20000){
                        set_skill("taoism", nlv / 10);
                        set("shen", 40000000 + nlv * 500);
                }
        }
 
                if (this_object()->query_skill_mapped("force") == "xixing-dafa") 
                        extstr = "suck";
                else
                        extstr = "recover";
                        
        set("chat_chance_combat", 120);
        if (strpfm3!=""){
                set("chat_msg_combat", ({
                (: perform_action, strpfm1 :),
                (: perform_action, strpfm2 :),
                (: perform_action, strpfm3 :),
                (: exert_function, extstr :),
                }) );
        }
        else if (strpfm2!=""){
                set("chat_msg_combat", ({
                (: perform_action, strpfm1 :),
                (: perform_action, strpfm2 :),
                (: exert_function, extstr :),
                }) );
        }
        else if (strpfm1!=""){
                set("chat_msg_combat", ({
                (: perform_action, strpfm1 :),
                (: exert_function, extstr :),
                }) );
        }

        if (elv > random(5) && fam=="峨眉") {
                new("/clone/medicine/guiyuan")->move(this_object());
                set("guiyuan", 1);
        }
        if (fam == "五毒"){
                                set_skill("poison", nlv);
                                set_skill("wudu-qishu", nlv);
                set_skill("wudu-jing", random(1400)+ 100);
                if (nlv > 20000){
                                        set_skill("wudu-jing", random(nlv / 10)+ 100);
                                        set_skill("poison", nlv*3);
                                        set_skill("wudu-qishu", nlv*3);
                }
                                map_skill("poison", "wudu-qishu"); 
                                set("can_perform/qianzhu-wandushou/jin", elv * 11);
                                set("family/family_name", "五毒教");
                                set("ability2/五毒教", ([
                                      "chance-bdjcg-cpin" : 25,
                                "n--bdjcg-grow2" : 25,
                                "reduce_damage-bdjcg" : 25,
                                "chance-bdjcg-protect" : 25,
                                "cd-qzwds-qzwd" : 5,
                                "da_power-bdjcg-wpin2" : 25,
                                "max-bdjcg-summon" : elv * 5,
                                "da_power-bdjcg-wpin3" : 25,
                                "da_power-bdjcg-wpin" : 25,
                                "ap_power-bdjcg-wpin" : 25,
                                "avoid_die-bdjcg" : 25,
                                "n-bdjcg-grow1" : 25,
                                "cd-bdjcg-summon" : 25,
                                "cd-bdjcg-wpin" : 25,
                                "hp-bdjcg" : 25,
                                ])
                                );
        }
}


void setlv(int tlv, int nt1, int nt2)
{
        int rnd, elv, idxn, ntmp, nsk/*, rndtmp*/;
        float fudmg;
        
        if (tlv >= 950)
                rnd = random(5);
        else if (tlv >= 800)
                rnd = random(15);
        else if (tlv >= 650)
                rnd = random(75);
        else if (tlv >= 550)
                rnd = random(225);
        else if (tlv >= 450)
                rnd = random(675);
        else if (tlv >= 350)
                rnd = random(2025);
        else if (tlv >= 250)
                rnd = random(6075);
        else if (tlv >= 150)
                rnd = random(9113);
        else
                rnd = random(15000 - tlv * 50);
                
        idxn = tlv / N_INCREASE;
        nsk = SK_BASE + to_int( SK_LV * pow(SK_XINCREASE, idxn) * (1 + SK_INCREASE * (tlv % N_INCREASE)) );
        
        if (nt1>-1) rnd = nt1;
        
        fudmg = 1.0;
        if (rnd < 3) {
                if (random(5)) set("no_nuoyi", 1); 
                elv = 9;
                set("elv", elv);
                nsk += elv * 20;
                if (tlv > 800) nsk += (tlv - 800) * 500;
                switch (((nt2>-1) ? nt2 : random(7)))
        {
                        case 0:
                                do_presk("江湖", nsk, "claw", "jiuyin-baiguzhao",  "qiankun-danuoyi", "shexing-lifan", "jiuyang-shengong", "", "", "","claw.zhua", "parry.yi", "claw.duo");
                                break;
                        case 1://霸刀
                                        fudmg = 20.0;
                                set("chance_summon", 5);
                                do_presk("少林", nsk, "finger", "yizhi-chan",  "jingang-buhuaiti", "shexing-lifan", "yijinjing", "/clone/weapon/jiedao", "blade", "badao","finger.dian", "parry.protect", "blade.san");
                                break;
                        case 2:
                                set("chance_summon", 10);
                                do_presk("魔教", nsk, "cuff", "nuquan",  "moshen-zhenshen", "jiutian-xiaoyaobu", "chiyou-kuangzhanjue", "/clone/weapon/blade", "blade", "moon-blade","parry.wu", "blade.yue", "blade.ting");
                                break;
                        case 3:
                                do_presk("五毒", nsk, "hand", "qianzhu-wandushou",  "qianzhu-wandushou", "wudu-yanluobu", "xiuluo-yinshagong", "", "", "","dodge.snake", "hand.chuan", "hand.jin");
                                break;
                                                case 4:
                                set("chance_perform", 12);//连续pfm
                                wield_wfile("/clone/weapon/sword");
                                do_presk("五毒", nsk, "hand", "qianzhu-wandushou",  "qianzhu-wandushou", "wudu-yanluobu", "xiuluo-yinshagong", "/clone/weapon/sword", "sword", "kuangfeng-jian","dodge.snake", "sword.yong", "hand.jin");
                                break;
                        case 5:
                                fudmg = 1.5;
                                set("chance_summon", 55);
                                set("lonely-sword/nothing",1);//无招
                                do_presk("华山", nsk, "strike", "hunyuan-zhang",  "qiankun-danuoyi", "feiyan-huixiang", "zixia-shengong", "/clone/weapon/sword", "sword", "lonely-sword","sword.hun", "sword.po", "sword.xiao");
                                break;
                        case 6:
                                do_presk("桃花", nsk, "finger", "tanzhi-shentong",  "qiankun-danuoyi", "shenxing-baibian", "yijinjing", "", "", "","finger.dian", "finger.po", "finger.zhuan");
                                break;
                }
        }
        else if (rnd < 15) {
                if (random(3)) set("no_nuoyi", 1); 
                elv = 8;
                set("elv", elv);
                nsk += elv * 20;
                if (tlv > 800) nsk += (tlv - 800) * 500;
                switch (((nt2>-1) ? nt2 :  random(9)))
        {
                        case 0:
                                do_presk("慕容", nsk, "finger", "canhe-zhi",  "douzhuan-xingyi", "shenxing-baibian", "yijinjing", "", "", "","finger.canhe", "finger.zhi", "parry.yi");
                                break;
                        case 1://太强……
                                do_presk("江湖", nsk, "unarmed", "mingyu-gong",  "mingyu-gong", "mingyu-gong", "mingyu-gong", "", "", "","unarmed.moqi", "unarmed.qiong", "");
                                break;
                        case 2://call die配合不坏和海量内力，高层后的噩梦
                                do_presk("少林", nsk, "finger", "yizhi-chan",  "jingang-buhuaiti", "shenxing-baibian", "yijin-duangu", "", "", "","finger.dian", "finger.jingmo", "parry.protect");
                                break;
                        case 3:
                                do_presk("丐帮", nsk, "strike", "dragon-strike",  "dragon-strike", "shexing-lifan", "huntian-qigong", "", "", "","strike.xiao", "strike.long", "strike.xianglong");
                                break;
                        case 4:
                                do_presk("古墓", nsk, "unarmed", "sad-strike",  "douzhuan-xingyi", "shexing-lifan", "surge-force", "", "", "","unarmed.tao", "unarmed.tuo", "unarmed.xiao");
                                break;
                        case 5:
                                set("chance_summon", 10);
                                do_presk("胡家", nsk, "strike", "tianchang-zhang",  "daojian-guizhen", "sixiang-bufa", "lengyue-shengong", "/clone/weapon/blade", "blade", "daojian-guizhen","blade.tian", "blade.tian", "blade.po");
                                break;
                        case 6:
                                do_presk("唐门", nsk, "hand", "boyun-suowu",  "boyun-suowu", "qiulin-shiye", "biyun-xinfa", "", "", "","hand.dian", "throwing.hua", "throwing.shijie");
                                break;
                        case 7:
                                fudmg = 0.1;
                                do_presk("峨眉", nsk, "strike", "piaoxue-zhang",  "piaoxue-zhang", "zhutian-bu", "linji-zhuang", "", "", "","strike.zhao", "finger.ling", "finger.ling");
                                break;
                        case 8:
                                do_presk("五毒", nsk, "hand", "qianzhu-wandushou",  "qianzhu-wandushou", "wudu-yanluobu", "xiuluo-yinshagong", "", "", "","dodge.snake", "hand.chuan", "hand.jin");
                                break;
                }
        }
        else if (rnd < 75) {
                        if (random(2)) set("no_nuoyi", 1); 
                elv = 7;
                set("elv", elv);
                nsk += elv * 20;
                switch (((nt2>-1) ? nt2 :  random(9)))
        {
                        case 0:
                                do_presk("桃花", nsk, "finger", "tanzhi-shentong",  "tanzhi-shentong", "shenxing-baibian", "yijinjing", "", "", "","finger.dian", "finger.po", "finger.zhuan");
                                break;
                        case 1://强
                                do_presk("江湖", nsk, "unarmed", "taixuan-gong",  "taixuan-gong", "taixuan-gong", "taixuan-gong", "", "", "","unarmed.xuan", "", "");
                                break;
                        case 2://威力弱，不配九阴神功之名
                                fudmg = 3.0;
                                do_presk("江湖", nsk, "claw", "jiuyin-shengong",  "jiuyin-shengong", "jiuyin-shengong", "jiuyin-shengong", "", "", "","claw.xin", "claw.zhua", "claw.zhua");
                                break;
                        case 3://虽然只是金刚指，但添加个日月鞭
                                set("chance_summon", 8);
                                do_presk("少林", nsk, "finger", "jingang-zhi",  "jingang-zhi", "shaolin-shenfa", "shaolin-xinfa", "/clone/weapon/whip", "whip", "riyue-bian","whip.chan", "finger.san", "whip.shang");
                                break;
                        case 4://小心控制恶心的刺目！
                                set("chance_summon", 5);
                                do_presk("日月", nsk, "unarmed", "pixie-jian",  "pixie-jian", "pixie-jian", "pixie-jian", "/d/fuzhou/npc/obj/xiuhua", "sword", "pixie-jian","unarmed.po", "unarmed.pi", "sword.duo");
                                break;
                        case 5:
                                        fudmg = 0.8;
                                set("chance_summon", 1);
                                do_presk("魔教", nsk, "cuff", "nuquan",  "moshen-zhenshen", "jiutian-xiaoyaobu", "chiyou-kuangzhanjue", "/clone/weapon/blade", "blade", "moon-blade","cuff.nu", "blade.yue", "");
                                break;
                        case 6:
                                set("chance_summon", 1);
                                do_presk("胡家", nsk, "strike", "tianchang-zhang",  "daojian-guizhen", "sixiang-bufa", "lengyue-shengong", "/clone/weapon/blade", "blade", "daojian-guizhen","strike.huang", "blade.tian", "blade.po");
                                break;
                        case 7:
                                do_presk("白驼", nsk, "strike", "hamagong",  "hamagong", "chanchu-bufa", "hamagong", "", "", "","strike.tui", "strike.puji", "strike.zhen");
                                break;
                        case 8:
                                fudmg = 0.1;
                                wield_wfile("/clone/weapon/sword");
                                do_presk("峨眉", nsk, "strike", "piaoxue-zhang",  "piaoxue-zhang", "zhutian-bu", "linji-zhuang", "/clone/weapon/sword", "sword", "yitian-jian","strike.zhao", "finger.ling", "sword.zhen");
                                break;
                }
        }
        else if (rnd < 225) {
                        if (!random(10)) set("no_nuoyi", 1); 
                elv = 6;
                set("elv", elv);
                nsk += elv * 20;
                switch (((nt2>-1) ? nt2 :  random(9)))
        {
                        case 0://偏弱，但配合毒和busy，尚可
                                do_presk("铁掌", nsk, "strike", "tie-zhang",  "tie-zhang", "shexing-lifan", "yijin-duangu", "", "", "","strike.juesha", "strike.yin", "strike.long");
                                break;
                        case 1://偏弱
                                fudmg = 1.8;
                                do_presk("星宿", nsk, "strike", "chousui-zhang",  "chousui-zhang", "shenxing-baibian", "freezing-force", "", "", "","strike.dan", "strike.tao", "");
                                break;
                        case 2:
                                do_presk("少林", nsk, "finger", "yizhi-chan",  "yizhi-chan", "yiwei-dujiang", "yijin-duangu", "", "", "","finger.dian", "finger.jingmo", "");
                                break;
                        case 3://虽然只是金刚指，但添加个轮回剑
                                set("chance_summon", 2);
                                do_presk("少林", nsk, "finger", "jingang-zhi",  "jingang-zhi", "shaolin-shenfa", "shaolin-xinfa", "/clone/weapon/sword", "sword", "lunhui-jian","finger.fumo", "finger.san", "sword.lun");
                                break;
                        case 4:
                                set("chance_summon", 3);
                                do_presk("日月", nsk, "unarmed", "pixie-jian",  "pixie-jian", "pixie-jian", "pixie-jian", "/d/fuzhou/npc/obj/xiuhua", "sword", "pixie-jian","unarmed.po", "unarmed.pi", "");
                                break;
                        case 5:
                                fudmg = 0.8;
                                wield_wfile("/clone/weapon/blade");
                                do_presk("魔教", nsk, "cuff", "nuquan",  "nuquan", "jiutian-xiaoyaobu", "chiyou-kuangzhanjue", "/clone/weapon/blade", "blade", "moon-blade","cuff.nu", "blade.yue", "");
                                break;
                        case 6:
                                wield_wfile("/clone/weapon/blade");
                                do_presk("胡家", nsk, "strike", "tianchang-zhang",  "daojian-guizhen", "sixiang-bufa", "lengyue-shengong", "/clone/weapon/blade", "blade", "daojian-guizhen","strike.huang", "blade.tian", "blade.xue");
                                break;
                        case 7:
                                do_presk("白驼", nsk, "strike", "hamagong",  "hamagong", "chanchu-bufa", "hamagong", "", "", "","strike.tui", "strike.puji", "strike.zhen");
                                break;
                        case 8:
                                do_presk("五毒", nsk, "hand", "qianzhu-wandushou",  "qianzhu-wandushou", "wudu-yanluobu", "xiuluo-yinshagong", "", "", "","dodge.snake", "hand.chuan", "hand.jin");
                                break;
                }
        }
        else if (rnd < 675) {
                        if (!random(20)) set("no_nuoyi", 1); 
                elv = 5;
                set("elv", elv);
                nsk += elv * 20;
                switch (((nt2>-1) ? nt2 :  random(9)))
        {
//                      case 0://pfm.c 37行错误
//                              do_presk("红花", nsk, "hand", "benlei-shou",  "benlei-shou", "shexing-lifan", "honghua-shengong", "", "", "","hand.yunkai", "", "");
//                              break;
                        case 0://太弱
                                fudmg = 5.0;
                                do_presk("全真", nsk, "cuff", "chunyang-quan",  "chunyang-quan", "shenxing-baibian", "xiantian-gong", "", "", "","cuff.wuji", "cuff.lianhuan", "");
                                break;
                        case 1://偏弱
                                fudmg = 4.0;
                                do_presk("雪山", nsk, "hand", "dashou-yin",  "dashou-yin", "shexing-lifan", "yijin-duangu", "", "", "","hand.yin", "", "");
                                break;
                        case 2://偏下，配合低级9j
                                //fudmg = 1.1;
                                set("chance_summon", 3);
                                set("lonely-sword/nothing",1);//无招
                                do_presk("华山", nsk, "strike", "hunyuan-zhang",  "hunyuan-zhang", "feiyan-huixiang", "zixia-shengong", "/clone/weapon/sword", "sword", "lonely-sword","sword.qi", "sword.po", "sword.xiao");
                                break;
                        case 3://狂风刀法
                                //fudmg = 0.6;
                                set("chance_perform", 5);//连续pfm
                                do_presk("江湖", nsk, "hand", "lanhua-shou",  "lanhua-shou", "fuguanglueying", "yijin-duangu", "/clone/weapon/blade", "blade", "kuangfeng-blade","hand.fei", "blade.kuang", "hand.fu");
                                break;
                        case 4:
                                fudmg = 0.8;
                                wield_wfile("/clone/weapon/blade");
                                do_presk("胡家", nsk, "strike", "tianchang-zhang",  "hujia-daofa", "sixiang-bufa", "lengyue-shengong", "/clone/weapon/blade", "blade", "hujia-daofa","strike.huang", "blade.pi", "blade.po");
                                break;
                        case 5:
                                fudmg = 1.6;
                                do_presk("武当", nsk, "cuff", "taiji-quan",  "taiji-quan", "tiyunzong", "taiji-shengong", "", "", "","cuff.tu", "cuff.yin", "cuff.an");
                                break;
                        case 6:
                                do_presk("白驼", nsk, "strike", "hamagong",  "hamagong", "chanchu-bufa", "hamagong", "", "", "","strike.tui", "strike.puji", "");
                                break;
                        case 7:
                                set("chance_summon", 8);
                                do_presk("日月", nsk, "hand", "huanmo-longtianwu",  "huanmo-longtianwu", "piaomiao-shenfa", "xixing-dafa", "/clone/weapon/sword", "sword", "yuanshi-jian", "sword.xuan", "sword.xuan", "");
                                break;
                        case 8://虽然只是金刚指，但添加个日月鞭
                                set("chance_summon", 5);
                                do_presk("少林", nsk, "finger", "jingang-zhi",  "jingang-zhi", "shaolin-shenfa", "shaolin-xinfa", "/clone/weapon/whip", "whip", "riyue-bian","finger.fumo", "finger.san", "whip.he");
                                break;
                }
        }
        else if (rnd < 2025) {
                elv = 4;
                set("elv", elv);
                nsk += elv * 20;
                switch (((nt2>-1) ? nt2 :  random(8)))
        {
                        case 0://威力太弱,busy高
                                fudmg = 6.5;
                                do_presk("丐帮", nsk, "hand", "shexing-diaoshou",  "shexing-diaoshou", "xiaoyaoyou", "huntian-qigong", "", "", "","hand.chan", "", "");
                                break;
                        case 1:
                                do_presk("江湖", nsk, "strike", "xuanming-zhang",  "xuanming-zhang", "shexing-lifan", "xuanming-shengong", "", "", "","strike.ying", "strike.lang", "strike.wuji");
                                break;
//                      case 2://pfm.c 39行错误
//                              do_presk("青城", nsk, "unarmed", "wuying-leg",  "wuying-leg", "chuanhua", "qingming-xuangong", "", "", "","unarmed.fanti", "", "");
//                              break;
                        case 2://太弱,添加天剑
                                fudmg = 6.0;
                                set("chance_summon", 1);
                                do_presk("江湖", nsk, "strike", "bizhen-qingzhang",  "bizhen-qingzhang", "shenxing-baibian", "yijin-duangu", "/clone/weapon/sword/changjian", "sword", "tianjian","strike.pengpai", "sword.lian", "");
                                break;
                        case 3://偏下，配合低级9j
                                fudmg = 0.9;
                                if (random(3)) set("lonely-sword/nothing",1);//无招
                                wield_wfile("/clone/weapon/sword");
                                do_presk("华山", nsk, "strike", "hunyuan-zhang",  "hunyuan-zhang", "feiyan-huixiang", "zixia-shengong", "/clone/weapon/sword", "sword", "lonely-sword","strike.wuji", "sword.po", "sword.xiao");
                                break;
                        case 4://弱
                                fudmg = 10;
                                wield_wfile("/clone/weapon/sword");
                                do_presk("峨眉", nsk, "finger", "tiangang-zhi",  "tiangang-zhi", "zhutian-bu", "linji-zhuang", "/clone/weapon/sword", "sword", "yitian-jian","finger.ling", "sword.fumo", "sword.yitian");
                                break;
                        case 5://狂风刀法
                                //fudmg = 0.5;
                                set("chance_perform", 2);//连续pfm
                                wield_wfile("/clone/weapon/blade");
                                do_presk("江湖", nsk, "hand", "lanhua-shou",  "lanhua-shou", "fuguanglueying", "yijin-duangu", "/clone/weapon/blade", "blade", "kuangfeng-blade","hand.fei", "blade.kuang", "hand.fu");
                                break;
                        case 6:
                                        set("chance_summon", 5);
                                wield_wfile("/clone/weapon/sword");
                                do_presk("日月", nsk, "hand", "huanmo-longtianwu",  "huanmo-longtianwu", "piaomiao-shenfa", "xixing-dafa", "/clone/weapon/sword", "sword", "yuanshi-jian", "sword.xuan", "sword.xuan", "");
                                break;
                        case 7:
                                do_presk("五毒", nsk, "hand", "qianzhu-wandushou",  "qianzhu-wandushou", "wudu-yanluobu", "xiuluo-yinshagong", "", "", "","dodge.snake", "hand.chuan", "");
                                break;
                }
        }
        else if (rnd < 6075) {
                elv = 3;
                set("elv", elv);
                nsk += elv * 20;
                switch (((nt2>-1) ? nt2 :  random(7)))
        {
                        case 0://偏下，配合低级9j
                                fudmg = 0.7;
                                set("lonely-sword/nothing",1);//无招
                                wield_wfile("/clone/weapon/sword");
                                do_presk("华山", nsk, "strike", "hunyuan-zhang",  "hunyuan-zhang", "feiyan-huixiang", "zixia-shengong", "/clone/weapon/sword", "sword", "lonely-sword","strike.wuji", "sword.po", "sword.yi");
                                break;
                        case 1://偏下
                                fudmg = 1.2;
                                do_presk("江湖", nsk, "finger", "huanyin-zhi",  "huanyin-zhi", "zhuangzi-wu", "yijin-duangu", "", "", "","finger.huanyin", "", "");
                                break;
                        case 2://弱
                                fudmg = 5;
                                wield_wfile("/clone/weapon/blade");
                                do_presk("峨眉", nsk, "strike", "piaoxue-zhang",  "piaoxue-zhang", "zhutian-bu", "linji-zhuang", "/clone/weapon/blade", "blade", "yanxing-dao","strike.yun", "strike.zhao", "blade.huan");
                                break;
                        case 3:
                                fudmg = 1.3;
                                do_presk("武当", nsk, "cuff", "taiji-quan",  "taiji-quan", "tiyunzong", "taiji-shengong", "", "", "","dodge.zong", "cuff.yin", "cuff.an");
                                break;
                        case 4:
                                do_presk("血刀", nsk, "unarmed", "shenzhaojing",  "shenzhaojing", "zhuangzi-wu", "shenzhaojing", "", "", "","unarmed.wu", "unarmed.ying", "");
                                break;
                        case 5:
                                set("chance_perform", 1);//连续pfm
                                wield_wfile("/clone/weapon/sword");
                                do_presk("华山", nsk, "strike", "hunyuan-zhang",  "hunyuan-zhang", "feiyan-huixiang", "zixia-shengong", "/clone/weapon/sword", "sword", "kuangfeng-jian","strike.wuji", "sword.yong", "sword.sao");
                                break;
                        case 6:
                                do_presk("五毒", nsk, "hand", "qianzhu-wandushou",  "qianzhu-wandushou", "wudu-yanluobu", "xiuluo-yinshagong", "", "", "","dodge.snake", "hand.chuan", "hand.wan");
                                break;
                }
        }
        else if (rnd < 9113) {
                elv = 2;
                set("elv", elv);
                nsk += elv * 20;
                switch (((nt2>-1) ? nt2 :  random(6)))
        {
                        case 0:
                                do_presk("日月", nsk, "claw", "shiying-shenzhao",  "shiying-shenzhao", "zhuangzi-wu", "yijin-duangu", "", "", "","claw.jueming", "", "");
                                break;
                        case 1:
                                do_presk("江湖", nsk, "finger", "xuantian-zhi",  "xuantian-zhi", "zhuangzi-wu", "xuantian-wujigong", "", "", "","finger.bing", "", "");
                                break;
//                      case 2:
//                              //pfm.c 34行错误
//                              //do_presk("衡山", nsk, "hand", "luoyan-hand",  "luoyan-hand", "henshan-shenfa", "huiyan-xinfa", "", "", "","hand.jinghan", "", "");
//                              break;
                        case 2:
                                        fudmg = 1.1;
                                do_presk("武当", nsk, "cuff", "taiji-quan",  "taiji-quan", "tiyunzong", "taiji-shengong", "/clone/weapon/blade", "blade", "xuanxu-dao","blade.huan", "cuff.zhan", "cuff.ji");
                                break;
                        case 3://偏上
                                fudmg = 0.8;
                                do_presk("少林", nsk, "finger", "yizhi-chan",  "yizhi-chan", "shaolin-shenfa", "shaolin-xinfa", "", "", "","finger.dian", "", "");
                                break;
                        case 4://狂风刀法
                                fudmg = 0.25;
                                set("chance_perform", 1);//连续pfm
                                wield_wfile("/clone/weapon/blade");
                                do_presk("江湖", nsk, "hand", "lanhua-shou",  "lanhua-shou", "fuguanglueying", "yijin-duangu", "/clone/weapon/blade", "blade", "kuangfeng-blade","hand.fei", "blade.kuang", "hand.fu");
                                break;
                        case 5://弱
                                fudmg = 1.5;
                                do_presk("峨眉", nsk, "strike", "piaoxue-zhang",  "piaoxue-zhang", "zhutian-bu", "linji-zhuang", "", "", "","strike.yun", "strike.yun", "strike.yun");
                                break;
                }
        }
        else if (rnd < 13669) {
                elv = 1;
                set("elv", elv);
                nsk += elv * 20;
                switch (((nt2>-1) ? nt2 :  random(7)))
        {
                        case 0:
                                do_presk("江湖", nsk, "strike", "jinshe-zhang",  "jinshe-zhang", "zhuangzi-wu", "yijin-duangu", "", "", "","strike.fugu", "", "");
                                break;
                        case 1:
                                do_presk("少林", nsk, "finger", "jingang-zhi",  "jingang-zhi", "shaolin-shenfa", "shaolin-xinfa", "", "", "","finger.fumo", "finger.san", "");
                                break;
                        case 2://偏上
                                fudmg = 0.8;
                                do_presk("江湖", nsk, "claw", "ningxue-shenzhao",  "ningxue-shenzhao", "shexing-lifan", "yijin-duangu", "", "", "","claw.ji", "", "");
                                break;
                        case 3://偏上
                                fudmg = 0.7;
                                do_presk("少林", nsk, "finger", "yizhi-chan",  "yizhi-chan", "shaolin-shenfa", "shaolin-xinfa", "", "", "","finger.jingmo", "", "");
                                break;
                        case 4://兰花拂穴手+越女剑
                                fudmg = 0.9;
                                do_presk("江湖", nsk, "hand", "lanhua-shou",  "lanhua-shou", "fuguanglueying", "yijin-duangu", "/clone/weapon/sword/xijian", "sword", "yuenv-jian","hand.fei", "sword.xin", "hand.fu");
                                break;
                        case 5:
                                do_presk("华山", nsk, "strike", "hunyuan-zhang",  "hunyuan-zhang", "feiyan-huixiang", "zixia-shengong", "", "", "","strike.wuji", "", "");
                                break;
                        case 6:
                                do_presk("五毒", nsk, "hand", "qianzhu-wandushou",  "qianzhu-wandushou", "wudu-yanluobu", "xiuluo-yinshagong", "", "", "","dodge.snake", "hand.wan", "hand.wan");
                                break;
                }
        }
        else {
                elv = 0;
                set("elv", elv);
                nsk += 0;//在此可以微调sk等级
                switch (((nt2>-1) ? nt2 :  random(7)))
        {
                        case 0:
                                do_presk("少林", nsk, "finger", "jingang-zhi",  "jingang-zhi", "shaolin-shenfa", "shaolin-xinfa", "", "", "","finger.fumo", "", "");
                                break;
                        case 1:
                                do_presk("白驼", nsk, "cuff", "lingshe-quan",  "lingshe-quan", "chanchu-bufa", "shaolin-xinfa", "", "", "","cuff.rou", "", "");
                                break;
                        case 2:
                                do_presk("灵鹫", nsk, "strike", "liuyang-zhang",  "liuyang-zhang", "lingbo-weibu", "bahuang-gong", "", "", "","strike.baihong", "", "");
                                break;
                        case 3:
                                do_presk("神龙", nsk, "hand", "shenlong-bashi",  "shenlong-bashi", "shexing-lifan", "yijin-duangu", "", "", "","hand.xian", "", "");
                                break;
                        case 4:
                                do_presk("丐帮", nsk, "hand", "chansi-shou",  "chansi-shou", "zhuangzi-wu", "yijin-duangu", "", "", "","hand.qin", "", "");
                                break;
                        case 5://兰花拂穴手+越女剑
                                fudmg = 0.6;
                                wield_wfile("/clone/weapon/sword/xijian");
                                do_presk("江湖", nsk, "hand", "lanhua-shou",  "lanhua-shou", "fuguanglueying", "yijin-duangu", "/clone/weapon/sword/xijian", "sword", "yuenv-jian","hand.fei", "sword.pengxin", "hand.fu");
                                break;
                        case 6:
                                do_presk("五毒", nsk, "hand", "qianzhu-wandushou",  "qianzhu-wandushou", "wudu-yanluobu", "xiuluo-yinshagong", "", "", "","hand.wan", "", "");
                                break;
                }
        }
        
        
                if (elv < 7) {
                        if (!random(3)) set_skill("count", nsk * 2 / (10-elv));
                }
                else {
                        if (random(9)) set_skill("count", nsk * 2 / (10-elv));
                }
                
                if (elv < 3) {
                        if (random(10)) set_skill("martial-cognize", nsk * 3 / (10-elv));
                }
                else {
                        set_skill("martial-cognize", nsk * 3 / (10-elv));
                }
                
        set_name(HIC + "灵感塔" + HIR + "囚徒" + NOR, ({ "qiu tu", "boss" }));
        set("age", 22 + elv * 5);
        set("str", 20 + elv * 5);
        set("dex", 20 + elv * 5);
        set("con", 20 + elv * 5);
        set("int", 20 + elv * 5);
        ntmp = to_int( HP_QI_BASE * pow(HP_QI_XINCREASE, idxn) * (1 + HP_QI_INCREASE * (tlv % N_INCREASE)) );
        set("max_qi", ntmp);
        set("eff_qi", ntmp);
        set("qi", ntmp);
        ntmp = to_int( ntmp * HP_JING_PERCENT );
        set("max_jing", ntmp);
        set("eff_jing", ntmp);
        set("jing", ntmp);
        ntmp = to_int( HP_QI_BASE * pow(HP_QI_XINCREASE, idxn) * (1 + HP_QI_INCREASE * (tlv % N_INCREASE)) );
        ntmp = to_int( ntmp * HP_NEILI_PERCENT );
        set("max_neili", ntmp);
        set("neili", ntmp);
        set("max_jingli", ntmp);
        set("jingli", ntmp);
        set("level", tlv + 19);
        set("combat_exp", 100000000 * tlv);
                //set("auto_perform", 1);
                set("reborn/times",random(elv));
                set("yuanshen", random(elv));
                
        set_temp("apply/dex", (666 + elv * 500)/10);
        set_temp("apply/str", 666 + elv * 500);
        set_temp("apply/con", (666 + elv * 500)/10);
        set_temp("apply/int", 666 + elv * 500);
        set_temp("apply/parry", 2000 + elv * 1350);
        set_temp("apply/dodge", 2000 + elv * 1350);
        set_temp("apply/attack", 3000 + elv * 1500);
        set_temp("apply/defense", 2000 + elv * 1350);
        fudmg = 1.0;//此行等于放弃修正dmg
        set_temp("apply/unarmed_damage", 5000 + to_int(elv * 3000 * fudmg) );
        set_temp("apply/damage", 5000 + to_int(elv * 3000 * fudmg));
        set_temp("apply/armor", 2000 + elv * 1350);
        
                set_temp("apply/add_blind", 1 + elv * 3);//    : "致盲",                       // weapon 终极兵器 致盲-让对手失明
                set_temp("apply/add_freeze", 3 + elv * 2);//   : "冰冻",                       // weapon 终极兵器 冰冻-迟缓，减缓对方攻击，攻击pfm速度降低，无任何防御，无躲闪，无招架，就是挨打
                set_temp("apply/add_burning", 5 + elv * 4);//  : "灼烧",                       // weapon 终极兵器 灼烧-一定时间内目标不停的减少内力和气血condition
                set_temp("apply/add_forget", 2 + elv * 4);//   : "遗忘",                       // weapon 终极防具 遗忘-使对方忘记所有技能的绝招add_oblivion   
                set_temp("apply/add_weak", 2 + elv * 5);//     : "虚弱",                       // weapon 终极兵器
                set_temp("apply/add_busy", 5 + elv * 5);//     : "忙乱",                       // weapon 终极兵器
                set_temp("apply/avoid_blind", 65 + elv * 3);//  : "忽视致盲",                   // armor/rings 终极防具
                set_temp("apply/avoid_freeze", 40 + elv * 10);// : "忽视冰冻",                   // armor/rings 终极防具
                set_temp("apply/avoid_burning", 60 + elv * 10);//: "忽视灼烧",                   // armor/rings 终极防具
                set_temp("apply/avoid_dizziness", 90);//: "忽视眩晕",                  // armor/rings 终极防具
                set_temp("apply/avoid_forget", 65 + elv * 5);// : "忽视遗忘",                   // armor/rings 终极兵器
                set_temp("apply/avoid_weak", 70 + elv * 5);//   : "忽视虚弱",                   // armor/rings 终极防具
                set_temp("apply/avoid_busy", 45 + elv * 5);//   : "忽视忙乱",                   // armor/rings 终极防具
                set_temp("apply/reduce_busy", 55 + elv * 5);//  : "化解忙乱",                   // armor/rings 终极防具
                set_temp("apply/reduce_damage", 11 + elv * 8);//  : 化解伤害",                   // armor 终极防具 
                set_temp("apply/ap_power", 25 + elv * 16);//  : "绝招攻击力",         // weapon/rings
                set_temp("apply/dp_power", 16 + elv * 15);//  : "绝招防御力",         // armor
                set_temp("apply/da_power", 10 + elv * 4);//  : "绝招伤害力",         // weapon/rings
                set_temp("apply/avoid_defense", 3 + elv * 3);//  : "攻击无视目标防御",   // weapon/rings
                set_temp("apply/avoid_parry", 3 + elv * 3);//  : "攻击无视目标招架",   // weapon/rings
                set_temp("apply/avoid_dodge", 3 + elv * 3);//  : "攻击无视目标躲闪",   // weapon/rings
                set_temp("apply/avoid_force", 3 + elv * 3);//  : "攻击无视内功防御",   // weapon/rings
                set_temp("apply/avoid_attack", 30 + elv * 5);//  : "无视目标特殊攻击",   // armor
                    //set("jiali", 10000 + tlv * 800); 
                    command("jiali max");
                
}


int accept_fight(object ob)
{
        kill_ob(ob);
        return -1;
}

int accept_kill(object ob)
{
        return 1;
}

int accept_hit(object ob)
{
        return 1;
}


void receive_damage(string type, int n)
{
        if (!random(4)) {
                this_object()->stop_busy();
                return;
        }
}

void unconcious()
{
        die(query_last_damage_from());
}

void cz_fang(object me)
{
        int i;
        i = me->query_skill("parry", 1);
        i += i / 6;
        set_skill("parry", i);
        i = me->query_skill("dodge", 1);
        i += i / 6;
        set_skill("dodge", i);
        i = me->query_skill("force", 1);
        i += i / 9;
        set_skill("force", i);
        i = query("max_qi");
        i += i / 10;
        set("max_qi", i);
        set("eff_qi", i);
        set("qi", i);
        i = query("max_jing");
        i += i / 10;
        set("max_jing", i);
        set("eff_jing", i);
        set("jing", i);
        addn_temp("apply/attack", query_temp("apply/attack") / 3 + 10000);
    addn_temp("apply/armor", query_temp("apply/armor") / 2);
    addn_temp("apply/damage", query_temp("apply/damage") * 2 / 3 + 10000);
    addn_temp("apply/unarmed_damage", query_temp("apply/unarmed_damage") * 2 / 3 + 10000);
    addn_temp("apply/ap_power", 10);
    addn_temp("apply/dp_power", 15);
    addn_temp("apply/da_power", 10);
}

void init()
{
//      int i;
        object /*ob,*/ me = this_object();
        if (playerp(this_player()) && !query("env/invisible", this_player())) {
                        set("enemy_player", this_player(), me);
                        me->stop_busy();
                                if (query("guiyuan")) {
                                        command("eat guiyuan dan");
                                        me->stop_busy();
                                }
                if (query("level") > random(100)) {//100级的npc百分百powerup
                        me->stop_busy();
                        command("exert shield");
                        me->stop_busy();
                        command("exert powerup");
                        me->stop_busy();
                        if (random(3)) command("exert zu");
                        me->stop_busy();
                        if (random(3)) command("exert huaxue");
                        me->stop_busy();
                        if (random(3)) command("exert freeze");
                        me->stop_busy();
                        if (random(3)) command("exert nizhuan");
                        me->stop_busy();
                        if (random(3)) command("exert reserve");
                        me->stop_busy();
                        if (random(3)) command("exert niepan");
                        me->stop_busy();
                        if (random(3)) command("exert fengyun");
                        me->stop_busy();
                        if (random(3)) command("perform dodge.fei");
                        me->stop_busy();
                                }
                                if (random(5)) {//先行披挂
                                        check_weapon();
                                        hand_throw();
                                }
                                
                                if (random(2)) me->stop_busy();
                                        else me->start_busy(1+random(3));
                                
                if (sscanf(base_name(environment()), "/d/kaifeng/linggt/%*s")) {
                                if (ttype()==2) {
                                        cz_fang(me);
                                                if (random(3)) me->stop_busy();//防御塔再次获得66%先行出手
                                }
                        kill_ob(this_player());
                }
        }
        me->reset_action();
}

void die(object killer)
{
         int showexp, elv;
        object dob;             // 打晕这个NPC的人
        int n;                  // 可以奖励的人的数目
        int exp;                // 需要瓜分的经验
        int pot;                // 需要瓜分的潜能
        object *t;              // 杀死我的人的队伍列表
        object tob, wiz;
        string diemsg;
//      int i;
//              object *inv;

//              object gift_ob;
//              string s_gift,*key_s_gift;
//              int gift_point;

        // 定义奖励物品列表
                mixed oblist;
                
                object env;
                
                
        object me,ob;
        
        me = this_object();
        elv = query("elv");
        
        if(random(100)>=(18 - elv*2) && //82%不能call die? 随elv更加难度,elv=9时完全不可能
         objectp(ob = previous_object(0)) &&
            sscanf(base_name(ob), "/kungfu/skill/%*s") ) {
                if (!random(10)) me->full_self();
                return;
        }
                
                oblist = query("oblist");


                // 通知当前房间，以便计算刷新
                env = environment(this_object());
                if (env && objectp(env)) env->npc_die(this_object());
        // 找到杀了我(NPC)或是打晕我的人
        if (! objectp(dob = killer))
                dob = query_last_damage_from();
                if (! objectp(dob)) 
                                dob = query_temp("last_opponent");
                if (! objectp(dob)) 
                                dob = query_temp("enemy_player");
                if (! objectp(dob)) {
                        if (objectp(environment())){
                        t = all_inventory(environment());
                        if (sizeof(t)>0) {
                                t = filter_array(t, (: $1->is_user() && !query("env/invisible", $1) :));
                                if (sizeof(t)>0) dob = t[0];
                        }
                        }
                }
                if (! objectp(dob))
                {
                        wiz = find_player("redl");
                        if (wiz) {
                                tell_object(wiz, HIG + "灵感塔：出现没有奖励对象的问题。\n" + NOR);
                        }
                        destruct(this_object());
                        return;
                }

        t = dob->query_team();

        if (objectp(dob) && environment(dob) == environment(this_object()))
        {
                exp = GIFT_EXP;
                pot = GIFT_EXP / 10;
       
                                if( query("level", dob) <= query("level") ) 
                                {
                                        exp = to_int(exp * (1 + (query("level") + 1 - query("level", dob)) / 100)  );//每高一级多%1
                                }
                                else if( query("level", dob) <= query("level")*1.5 )
                                {
                                        exp /= 2;
                                        pot /= 2;
                                }
                                else if( query("level", dob) <= query("level")*2 )
                                {
                                        exp /= 4;
                                        pot /= 4;
                                }
                                else 
                                {
                                        exp = 100;
                                        pot = 100;
                                }
                                
                
                exp = to_int(exp * (random(100)+950) / 1000);
                                exp = invert_reborngiftd(dob, exp);
                                pot = exp / 8;
                showexp = exp;  
                addn("lgt/texp", get_show_giftexp(dob, showexp), dob);              
                                
//                              CHANNEL_D->channel_broadcast(CHANL_NAME, 
//                                      query("name", dob) + NOR + "击败"+ query("name") +NOR+"，获得"+chinese_number(get_show_giftexp(dob, showexp))+"点经验奖励。"
//                                      );
                                        
                                
                n = 0;
                n = sizeof(t);

                                if (n > 1)
                                {
                                        exp /= n;
                                        pot /= n;
                                }

                                if (n)
                                {                                
                                        foreach(tob in t)
                                        {
                                                   if (objectp(tob) && living(tob) && environment(tob) == environment(this_object()))
                                                {
                                                                   GIFT_D->delay_bonus(tob,
                                                                          ([ "exp"      : exp + ((tob == dob) ? exp / 10 : 0),
                                                                                 "pot"      : pot + ((tob == dob) ? pot / 10 : 0),
                                                                                 "prompt"   : "你的队伍杀死" + name() + "之后"]));

                                                 }
                                        }
                                }
                                else
                                {
                                        if (ttype()==2) diemsg = "抵抗";
                                                else if (ttype()==1) diemsg = "杀死";
                                                                   GIFT_D->delay_bonus(dob,
                                                                          ([ "exp"      : exp,
                                                                                 "pot"      : pot,
                                                                                 "prompt"   : "你在" + diemsg + name() + "之后"]));
                                }

        }

                                ob = query("myweapon",me);
                                if(objectp(ob)) destruct(ob);
                                if (environment() && objectp(environment())) environment(this_object())->pass(dob);
                destruct(this_object());

        return;
}




void create()
{
//      object ob; 
        set_name(HIC + "灵感塔" + HIR + "囚徒" + NOR, ({ "qiu tu", "boss" }));
        //set("nickname", NOR + "某某派高手" + NOR);
        set("age", 1);
        set("str", 1);
        set("dex", 1);
        set("con", 1);
        set("int", 1);
        set("max_qi", 1);
        set("eff_qi", 1);
        set("qi", 1);
        set("max_jing",1);
        set("eff_jing", 1);
        set("jing", 1);
        set("max_neili", 1);
        set("neili", 1);
        set("max_jingli", 1);
        set("jingli", 1);
        set("level", 1);
        set("combat_exp", 1);
                set("jiali", 1);
      
        
        setup();
        
}

