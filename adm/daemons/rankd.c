// rankd.c
// 1996-02-15 dts ranking related to "shen"

// #pragma optimize
// #pragma save_binary

#include <ansi.h>

string query_rank(object ob)
{
//      mapping fam;
        mapping toplist;

        int shen;
        int budd;
        int tao;
        int exp;
        int age;
        int eatman;
        int i;
        string fname;

        if (ob->is_ghost())
                return HIB "【 鬼  魂 】" NOR;

        if( query("reborn/times", ob) )
        {
                if( query("reborn/times", ob) == 3 )
                        return HIR "【元神三世】" NOR;
                if( query("reborn/times", ob) == 2 )
                        return HIR "【元神二世】" NOR;
                return HIR "【元神转世】" NOR;
        }

        toplist = COMPETE_D->query_tops();

        if (sizeof(toplist))
        {
                for (i = 0;i < sizeof(toplist);i ++)
                        if( toplist[i]["id"] == query("id", ob) )
                                return HIW + "【天下第" + NOR + HIY +
                                       chinese_number(i + 1) + NOR + HIW + "】" + NOR;
        }

        if( query("is_vendor", ob) )
        {
                if (ob->query_profit() >= 100000000000)
                        return HIY "【 商  王 】" NOR;
                else if (ob->query_profit() >= 50000000000)
                        return HIY "【商业巨头】" NOR;
                else if (ob->query_profit() >= 10000000000)
                        return HIY "【大 财 主】" NOR;
                else if (ob->query_profit() >= 5000000000)
                        return HIY "【 财  主 】" NOR;
                else if (ob->query_profit() >= 1000000000)
                        return HIY "【大 掌 柜】" NOR;
                else if (ob->query_profit() >= 500000000)
                        return HIY "【 掌  柜 】" NOR;
                else if (ob->query_profit() >= 100000000)
                        return HIY "【 货  商 】" NOR;
                else if (ob->query_profit() >= 50000000)
                        return HIY "【 货  郎 】" NOR;
                else if (ob->query_profit() >= 10000000)
                        return HIY "【 小  商 】" NOR;
                else    return HIY "【 小  贩 】" NOR;
        }

        shen=query("shen", ob);
        exp=query("exp", ob);
        age=query("age", ob);
        budd = ob->query_skill("buddhism", 1);
        tao  = ob->query_skill("taoism", 1);
        eatman=query("combat/eatman", ob);
        fname=query("family/family_name", ob);

        if( query("rank_info/rank", ob) )
                return HIY"【"+query("rank_info/rank", ob)+"】"NOR;

        switch (fname)
        {
                case "峨嵋派": budd = ob->query_skill("mahayana", 1); break;
                case "少林派": budd = ob->query_skill("buddhism", 1); break;
                case "武当派":
                case "全真教": budd = ob->query_skill("taoism", 1); break;
                case "华山派": budd = ob->query_skill("sword", 1); break;
                case "凌霄城":
                case "嵩山派": budd = ob->query_skill("sword", 1); break;
                case "古墓派": budd = ob->query_skill("yunv-xinfa", 1); break;
                case "慕容世家": budd = ob->query_skill("douzhuan-xingyi", 1); break;
                case "明教" :
                        budd = ob->query_skill("jiuyang-shengong", 1);
                        if (!budd)
                                budd = ob->query_skill("shenghuo-shengong", 1);
                        break;
                case"丐帮":budd=query("family/beggarlvl", ob);break;
                case "神龙岛": budd = ob->query_skill("busi-shenlong", 1); break;
                case "铁掌帮": budd = ob->query_skill("tiezhang-zhangfa", 1); break;
                case "段氏皇族": budd = ob->query_skill("kurong-changong", 1); break;
                case "雪山寺": budd = ob->query_skill("longxiang-gong", 1); break;
                case "桃花岛": budd = ob->query_skill("qimen-wuxing", 1); break;
                case "唐门世家":
                case "五毒教":
                case "星宿派": budd = ob->query_skill("poison", 1);     break;
                case "日月神教": budd = ob->query_skill("xixing-dafa", 1);      break;
                case "逍遥派": budd = ob->query_skill("beiming-shengong", 1);   break;
                case "灵鹫宫": budd = ob->query_skill("bahuang-gong", 1);       break;
                case "关外胡家": budd = ob->query_skill("lengyue-shengong", 1); break;
                case "欧阳世家": budd = ob->query_skill("hamagong", 1); break;
                case "血刀门": budd = ob->query_skill("xuedao-daofa", 1);       break;
                case "魔教": budd = ob->query_skill("moon-blade", 1);   break;
        } // switch (fname)

        switch(query("gender", ob) )
        {
                case "无性":
                        switch(wizhood(ob))
                        {
                                case "(boss)": return HIW "【 天  妖 】" NOR;
                                case "(admin)": return HIW "【 天  妖 】" NOR;
                                case "(assist)": return HIR "【 妖  官 】" NOR;
                                case "(arch)": return HIY "【 妖  神 】" NOR;
                                case "(wizard)": return HIG "【 妖  仙 】" NOR;
                                case "(apprentice)": return HIC "【 妖  女 】" NOR;
                                case "(immortal)": return HIC "【 妖  巫 】" NOR;
                                default:
                                        budd = (int)ob->query_skill("pixie-jian", 1);
                                        if( budd >= 2000) return HIR "【 九千岁 】"NOR;
                                        if( budd >= 1800) return HIR "【 厂  公 】"NOR;
                                        if( budd >= 1500) return HIR "【 大档头 】"NOR;
                                        if( budd >= 1200) return HIM "【东厂千户】"NOR;
                                        if( budd >= 900)  return MAG "【东厂百户】"NOR;
                                        if( budd >= 600) return MAG "【太监总管】"NOR;
                                        if( budd >= 300) return MAG "【 太  监 】"NOR;
                                        return MAG "【 小太监 】" NOR;
                        }
                case "女性":
                case "雌性":
                        switch(wizhood(ob))
                        {
                                case "(boss)": return HIW "【 天  仙 】" NOR;
                                case "(admin)": return HIW "【 天  仙 】" NOR;
                                case "(assist)": return HIR "【 女神官 】" NOR;
                                case "(arch)": return HIY "【 龙  女 】" NOR;
                                case "(wizard)": return HIG "【 仙  子 】" NOR;
                                case "(apprentice)": return HIC "【 飞  天 】" NOR;
                                case "(immortal)": return HIC "【 女顾问 】" NOR;
                                default:
                                        if( query("combat/PKS", ob) > 20 && query("combat/PKS", ob) > query("combat/MKS", ob) / 4 )
                                                return HIR "【杀人女魔】" NOR;
                                        if( query("thief", ob)>10 )
                                                return "【 女惯窃 】";
                                        switch(fname) {
                                                case "明教":
                                                        if(budd >= 2000) return HIR "【 圣  女 】" NOR;
                                                        if(budd >= 1700) return HIR "【宝树神姬】" NOR;
                                                        if(budd >= 1400) return RED "【 护法王 】" NOR;
                                                        if(budd >= 1000) return RED "【天门香主】" NOR;
                                                        if(budd >= 600) return HIM "【 女香主 】" NOR;
                                                        if(budd >= 200) return CYN "【 女教众 】" NOR;
                                                        return CYN "【 侍  女 】" NOR;
                                                case "丐帮":
                                                        if(budd >= 11) return HIW "【 帮  主 】" NOR;
                                                        if(budd >= 10) return HIW "【 副帮主 】" NOR;
                                                        if(budd >= 9) return HIC "【 长  老 】" NOR;
                                                        if(budd >= 6) return HIG "【 龙  头 】" NOR;
                                                        if(budd >= 5) return HIM "【 女舵主 】" NOR;
                                                        if(budd >= 4) return HIM "【 女香主 】" NOR;
                                                        if(budd >= 2) return HIM "【 女帮众 】" NOR;
                                                        return CYN "【 叫化婆 】" NOR;
                                                case "峨嵋派":
                                                        if( query("class", ob) != "bonze")break;
                                                        if (budd >= 600) return HIW "【 神  尼 】" NOR;
                                                        if (budd >= 400) return HIW "【 长  老 】" NOR;
                                                        if (budd >= 90)  return HIW "【 师  太 】" NOR;
                                                        if (budd >= 60) return HIW "【 比丘尼 】" NOR;
                                                        if (budd >= 30 || age >= 20) return HIW "【 沙弥尼 】" NOR;
                                                        return HIW "【 学戒女 】" NOR;
                                                case "雪山寺":
                                                        if (budd >= 1800 && shen >= 0) return HIY "【 欢喜佛 】" NOR;
                                                        if (budd >= 1800 && shen < 0) return HIY "【 欢喜魔 】" NOR;
                                                        if (budd >= 1400) return HIW "【 神  女 】" NOR;
                                                        if (budd >= 900)  return HIW "【 飞  天 】" NOR;
                                                        if (budd >= 600) return HIW "【 乾达婆 】" NOR;
                                                        if (budd >= 300 || age >= 20) return HIW "【 神妙女 】" NOR;
                                                        return HIW "【 授  事 】" NOR;
                                                case "桃花岛":
                                                        if (budd >= 1800) return HIW "【 逸  仙 】" NOR;
                                                        if (budd >= 1400) return HIC "【 逸  贤 】" NOR;
                                                        if (budd >= 1000) return WHT "【 逸  士 】" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "【 青  衣 】" NOR;
                                                        return "【 民  女 】";
                                                case "逍遥派":
                                                        if (budd >= 1800) return HIW "【 逸  仙 】" NOR;
                                                        if (budd >= 1400) return HIC "【 逸  贤 】" NOR;
                                                        if (budd >= 1000) return WHT "【 逸  士 】" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "【 青  衣 】" NOR;
                                                        return "【 民  女 】";
                                                case "华山派":
                                                        if (budd >= 1400) return HIY "【 剑  仙 】" NOR;
                                                        if (budd >= 1000) return HIC "【 女剑侠 】" NOR;
                                                        if (budd >= 500 || age >= 18)  return YEL "【 女剑客 】" NOR;
                                                        return "【 女剑手 】";
                                                case "嵩山派":
                                                case "凌霄城":
                                                        if (budd >= 1800) return HIW "【 剑  圣 】" NOR;
                                                        if (budd >= 1400) return HIY "【 剑  仙 】" NOR;
                                                        if (budd >= 1000) return HIC "【 女剑侠 】" NOR;
                                                        if (budd >= 500 || age >= 18)  return YEL "【 女剑客 】" NOR;
                                                        return "【 女剑手 】";
                                                case "古墓派":
                                                        if (budd >= 1800) return HIW "【 玉  女 】" NOR;
                                                        if (budd >= 1400) return HIY "【 倩  女 】" NOR;
                                                        if (budd >= 1000) return HIC "【 素  女 】" NOR;
                                                        if (budd >= 500 || age >= 18)  return YEL "【 琴  女 】" NOR;
                                                        return "【 琴  童 】";
                                                case "武当派":
                                                case "全真教":
                                                        if (budd >= 600) return HIY "【 玄  女 】" NOR;
                                                        if (budd >= 400) return HIY "【 仙  姑 】" NOR;
                                                        if (budd >= 100) return HIY "【 散  人 】" NOR;
                                                        if (budd >= 50 || age >= 20) return HIY "【 道  姑 】" NOR;
                                                        return "【 小道姑 】";
                                                case "铁掌帮":
                                                        if (budd >= 1800) return WHT "【 大当家 】" NOR;
                                                        if (budd >= 1400) return HIC "【 寨  主 】" NOR;
                                                        if (budd >= 1000) return CYN "【 大头目 】" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "【 头  目 】" NOR;
                                                        return "【 小喽罗 】";
                                                case "五毒教":
                                                case "唐门世家":
                                                case "星宿派":
                                                        if (budd >= 600) return HIB "【 毒  后 】" NOR;
                                                        if (budd >= 500) return YEL "【 毒  姬 】" NOR;
                                                        if (budd >= 400) return MAG "【 毒  妖 】" NOR;
                                                        if (budd >= 100) return BLU "【 毒罗刹 】" NOR;
                                                        if (budd >= 50 || age >= 18)  return CYN "【 毒  怪 】" NOR;
                                                        return "【 马屁虫 】";
                                                case "慕容世家":
                                                        if(budd >= 1900) return HIC "【 小  姐 】" NOR;
                                                        if(budd >= 1500) return HIC "【 庄  主 】" NOR;
                                                        if(budd >= 1100) return HIC "【 管  家 】" NOR;
                                                        if(budd >= 700) return HIC "【 侍  书 】" NOR;
                                                        if(budd >= 300) return HIC "【 大丫鬟 】" NOR;
                                                        return HIC "【 丫  鬟 】" NOR;
                                                case "灵鹫宫":
                                                        if(budd >= 1900) return HIC "【 玄  女 】" NOR;
                                                        if(budd >= 1500) return HIC "【 仙  子 】" NOR;
                                                        if(budd >= 1100) return HIC "【 天  女 】" NOR;
                                                        if(budd >= 700) return HIC "【逍遥女仙】" NOR;
                                                        if(budd >= 300) return HIC "【 仙  姑 】" NOR;
                                                        return HIC "【 仙  姑 】" NOR;
                                                case "日月神教":
                                                        if(budd >= 1900) return HIC "【 仙  姑 】" NOR;
                                                        if(budd >= 1500) return HIC "【 左护法 】" NOR;
                                                        if(budd >= 1100) return HIC "【 堂  主 】" NOR;
                                                        if(budd >= 700) return HIC "【 坛  主 】" NOR;
                                                        if(budd >= 300) return HIC "【 香  主 】" NOR;
                                                        return HIC "【 女教徒 】" NOR;
                                                case "段氏皇族":
                                                        if(budd >= 1900) return HIC "【 王  妃 】" NOR;
                                                        if(budd >= 1500) return HIC "【诰命夫人】" NOR;
                                                        if(budd >= 1100) return HIC "【 女  官 】" NOR;
                                                        if(budd >= 700) return HIC "【 女  官 】" NOR;
                                                        if(budd >= 300) return HIC "【 女  侍 】";
                                                        return HIC "【 女  侍 】";
                                                case "关外胡家":
                                                        if(budd >= 1900) return HIC "【雪山飞狐】" NOR;
                                                        if(budd >= 1500) return HIW "【 美刀王 】" NOR;
                                                        if(budd >= 1100) return HIC "【 刀  侍 】" NOR;
                                                        if(budd >= 700) return HIC "【 刀  奴 】" NOR;
                                                        if(budd >= 300) return YEL "【 刀  童 】" NOR;
                                                        return HIC "【 刀  童 】";
                                                case "魔教":
                                                        if(budd >= 2000) return HIR "【 魔  女 】" NOR;
                                                        if(budd >= 1700) return HIR "【 妖  姬 】" NOR;
                                                        if(budd >= 1400) return HIR "【护教圣女】" NOR;
                                                        if(budd >= 1000) return RED "【 使  者 】" NOR;
                                                        if(budd >= 600) return RED "【 侍  女 】" NOR;
                                                        if(budd >= 200) return CYN "【 教  徒 】" NOR;
                                                        return CYN "【 教  徒 】" NOR;
                                                case "欧阳世家":
                                                        if(budd >= 1900) return HIC "【西域狂魔】" NOR;
                                                        if(budd >= 1500) return HIC "【域外女魔】" NOR;
                                                        if(budd >= 1100) return HIC "【飞天魔女】" NOR;
                                                        if(budd >= 700) return HIC "【白衣姬人】" NOR;
                                                        if(budd >= 300) return HIC "【白衣少女】" NOR;
                                                        return HIC "【白衣少女】";
                                        } // switch(fname)

                                        if( !query("class", ob)){
                                                if (shen >= 1500000) return HIC "【巾帼神女】" NOR;
                                                if (shen >= 1000000) return HIC "【绝世天娇】" NOR;
                                                if (shen >= 500000) return HIC "【旷世女侠】" NOR;
                                                if (shen >= 50000) return HIC "【 女飞侠 】" NOR;
                                                if (shen >= 5000) return HIC "【 女  侠 】" NOR;
                                                if (shen >= 500) return HIC "【 小侠女 】" NOR;
                                                if (shen <= -1500000) return HIB "【 妖  姬 】" NOR;
                                                if (shen <= -1000000) return HIB "【灭世罗刹】" NOR;
                                                if (shen <= -500000) return HIB "【旷世女魔】" NOR;
                                                if (shen <= -50000) return HIB "【 女魔王 】" NOR;
                                                if (shen <= -5000) return HIB "【 女魔头 】" NOR;
                                                if (shen <= -500) return HIB "【 小魔女 】" NOR;
                                        }

                                        // 没有门派的才搬用这里的
                                        switch(query("class", ob)){
                                                case "bonze": return "【 尼 姑 】";
                                                case "taoist":
                                                        if (age >= 20) return "【 道  姑 】";
                                                        return "【 小道姑 】";
                                                case "bandit": return "【 女飞贼 】";
                                                case "dancer": return GRN"【 舞  妓 】"NOR;
                                                case "scholar": return "【 才  女 】";
                                                case "officer": return "【 女  官 】";
                                                case "fighter": return "【 女武者 】";
                                                case "swordsman": return "【 女剑士 】";
                                                case "alchemist": return "【 女方士 】";
                                                case "shaman": return "【 女巫医 】";
                                                case "beggar": return "【 叫化婆 】";
                                                default:
                                                        if( query("couple", ob)){
                                                                if (age < 30) return "【 少  妇 】";
                                                                if (age < 50) return "【中年妇人】";
                                                                return "【 老妇人 】";
                                                        }

                                                        if (age < 18) return "【 少  女 】";
                                                        if (age < 30) return "【青年女子】";
                                                        if (age < 50) return "【中年女子】";
                                                        return "【 老处女 】";
                                        }//switch( query("class", ob) )

                        } // switch(wizhood(ob))
                default:
                        switch(wizhood(ob)) {
                                case "(boss)": return HIY "【 天  神 】" NOR;
                                case "(admin)": return HIW "【 天  神 】" NOR;
                                case "(assist)": return HIR "【 神  官 】" NOR;
                                case "(arch)": return HIY "【 龙  神 】" NOR;
                                case "(wizard)": return HIG "【 仙  人 】" NOR;
                                case "(apprentice)": return HIC "【 巫  师 】" NOR;
                                case "(immortal)": return HIC "【 顾  问 】" NOR;
                                default:
                                        if( query("combat/PKS", ob) > 20 && query("combat/PKS", ob) > query("combat/MKS", ob) / 4 )
                                                return HIR "【杀人魔王】" NOR;
                                        if( query("thief", ob)>10 )
                                                return "【 惯  窃 】";
                                        switch(fname) {
                                                case "明教":
                                                        if(budd >= 2000) return HIW "【 副教主 】" NOR;
                                                        if(budd >= 1700) return WHT "【光明使者】" NOR;
                                                        if(budd >= 1400) return HIC "【护教法王】" NOR;
                                                        if(budd >= 1000) return HIC "【五旗护法】" NOR;
                                                        if(budd >= 600) return HIC "【 香  主 】" NOR;
                                                        if(budd >= 200) return CYN "【 教  众 】" NOR;
                                                        return CYN "【 杂  役 】" NOR;
                                                case "桃花岛":
                                                        if (budd >= 1800) return HIW "【 隐  圣 】" NOR;
                                                        if (budd >= 1400) return HIC "【 隐  贤 】" NOR;
                                                        if (budd >= 1000) return WHT "【 隐  士 】" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "【 门  生 】" NOR;
                                                        return "【 平  民 】";
                                                case "逍遥派":
                                                        if (budd >= 1800) return HIW "【 隐  圣 】" NOR;
                                                        if (budd >= 1400) return HIC "【 隐  贤 】" NOR;
                                                        if (budd >= 1000) return WHT "【 隐  士 】" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "【 门  生 】" NOR;
                                                        return "【 平  民 】";
                                                case "铁掌帮":
                                                        if (budd >= 1800) return WHT "【 山大王 】" NOR;
                                                        if (budd >= 1400) return HIC "【 寨  主 】" NOR;
                                                        if (budd >= 1000) return CYN "【 当  家 】" NOR;
                                                        if (budd >= 500 || age >= 18)  return CYN "【 头  目 】" NOR;
                                                        return "【 小喽罗 】";
                                                case "丐帮":
                                                        if(budd >= 11) return HIW "【 帮  主 】" NOR;
                                                        if(budd >= 10) return HIW "【 副帮主 】" NOR;
                                                        if(budd >= 9) return HIC "【 长  老 】" NOR;
                                                        if(budd >= 6) return HIG "【 龙  头 】" NOR;
                                                        if(budd >= 5) return HIM "【 舵  主 】" NOR;
                                                        if(budd >= 4) return HIM "【 香  主 】" NOR;
                                                        if(budd >= 2) return CYN "【 帮  众 】" NOR;
                                                        return CYN "【 叫化子 】" NOR;
                                                case "少林派":
                                                        if( query("class", ob) != "bonze" )
                                                                return HIY "【 行  者 】" NOR;
                                                        if (budd >= 600) return HIY "【 神  僧 】" NOR;
                                                        if (budd >= 500) return HIY "【 圣  僧 】" NOR;
                                                        if (budd >= 400) return HIY "【 长  老 】" NOR;
                                                        if (budd >= 300) return HIY "【 罗  汉 】" NOR;
                                                        if (budd >= 200) return HIY "【 尊  者 】" NOR;
                                                        if (budd >= 100) return HIY "【 禅  师 】" NOR;
                                                        if (budd >= 50) return HIY "【 比  丘 】" NOR;
                                                        return HIY "【 僧  侣 】" NOR;
                                                case "雪山寺":
                                                        if (budd >= 1800)
                                                                if (shen >= 0) return HIY "【欢喜法王】" NOR;
                                                                else return HIY "【欢喜魔王】" NOR;
                                                        if (budd >= 1400) return HIY "【 天  王 】" NOR;
                                                        if (budd >= 900)  return HIY "【 大护法 】" NOR;
                                                        if (budd >= 600) return HIY "【 金  刚 】" NOR;
                                                        if (budd >= 300 || age >= 20) return HIY "【 力  士 】" NOR;
                                                        return HIY "【 杂  役 】" NOR;
                                                case "华山派":
                                                        if (budd >= 1400) return HIY "【 剑  狂 】" NOR;
                                                        if (budd >= 1000) return HIC "【 剑  侠 】" NOR;
                                                        if (budd >= 500 || age >= 18) return YEL "【 剑  客 】" NOR;
                                                        return "【 剑  手 】";
                                                case "嵩山派":
                                                case "凌霄城":
                                                        if (budd >= 1800) return HIW "【 剑  宗 】" NOR;
                                                        if (budd >= 1400) return HIY "【 剑  狂 】" NOR;
                                                        if (budd >= 1000) return HIC "【 剑  侠 】" NOR;
                                                        if (budd >= 500 || age >= 18) return YEL "【 剑  客 】" NOR;
                                                        return "【 剑  手 】";
                                                case "古墓派":
                                                        if (budd >= 1800) return HIW "【 情  狂 】" NOR;
                                                        if (budd >= 1400) return HIY "【 情  痴 】" NOR;
                                                        if (budd >= 1000) return HIC "【 情  侠 】" NOR;
                                                        if (budd >= 500 || age >= 18) return YEL "【 剑  郎 】" NOR;
                                                        return "【 剑  童 】";
                                                case "武当派":
                                                case "全真教":
                                                        if (budd >= 600) return HIW "【 天  尊 】" NOR;
                                                        if (budd >= 400) return HIW "【 天  师 】" NOR;
                                                        if (budd >= 100) return HIW "【 真  人 】" NOR;
                                                        if (budd >= 50 || age >= 20) return HIW "【 道  士 】" NOR;
                                                        return "【 道  童 】";
                                                case "唐门世家":
                                                case "五毒教":
                                                case "星宿派":
                                                        if (budd >= 600) return HIB "【 毒  尊 】" NOR;
                                                        if (budd >= 500) return YEL "【 毒  霸 】" NOR;
                                                        if (budd >= 400) return MAG "【 毒  君 】" NOR;
                                                        if (budd >= 100) return BLU "【 毒  王 】" NOR;
                                                        if (budd >= 50 || age >= 18)  return CYN "【 毒  魔 】" NOR;
                                                        return "【 法螺王 】";
                                                case "慕容世家":
                                                        if(budd >= 1900) return HIC "【 少  爷 】" NOR;
                                                        if(budd >= 1500) return HIC "【 庄  主 】" NOR;
                                                        if(budd >= 1100) return HIC "【 管  家 】" NOR;
                                                        if(budd >= 700) return HIC "【 护  院 】" NOR;
                                                        if(budd >= 300) return HIC "【 庄  丁 】" NOR;
                                                        return HIC "【 庄  丁 】" NOR;
                                                case "日月神教":
                                                        if(budd >= 1900) return HIC "【 副教主 】" NOR;
                                                        if(budd >= 1500) return HIC "【 左护法 】" NOR;
                                                        if(budd >= 1100) return HIC "【 堂  主 】" NOR;
                                                        if(budd >= 700) return HIC "【 坛  主 】" NOR;
                                                        if(budd >= 300) return HIC "【 香  主 】" NOR;
                                                        return HIC "【 教  徒 】" NOR;
                                                case "段氏皇族":
                                                        if(budd >= 1900) return HIC "【 亲  王 】" NOR;
                                                        if(budd >= 1500) return HIC "【 侯  爷 】" NOR;
                                                        if(budd >= 1100) return HIC "【 将  官 】" NOR;
                                                        if(budd >= 700) return HIC "【 侍  卫 】" NOR;
                                                        if(budd >= 300) return HIC "【 校  尉 】" NOR;
                                                        return HIC "【 兵  士 】" NOR;
                                                case "关外胡家":
                                                        if(budd >= 1900) return HIC "【雪山飞狐】" NOR;
                                                        if(budd >= 1500) return HIW "【 美刀王 】" NOR;
                                                        if(budd >= 1100) return HIC "【 刀  侍 】" NOR;
                                                        if(budd >= 700) return HIC "【 刀  奴 】" NOR;
                                                        if(budd >= 300) return YEL "【 刀  童 】" NOR;
                                                        return HIC "【 刀  童 】";
                                                case "血刀门":
                                                        if (budd >= 1900)
                                                                if (shen >= 0) return HIR "【 魔中侠 】" NOR;
                                                        if(budd >= 1900) return HIR "【塞外刀魔】" NOR;
                                                        if(budd >= 1500) return HIC "【 刀  魔 】" NOR;
                                                        if(budd >= 700) return HIC "【 刀  侍 】" NOR;
                                                        if(budd >= 300) return HIC "【 刀  童 】" NOR;
                                                        return HIC "【 刀  童 】";
                                                case "魔教":
                                                        if(budd >= 2000) return HIR "【魔教至尊】" NOR;
                                                        if(budd >= 1700) return HIR "【 狂  魔 】" NOR;
                                                        if(budd >= 1400) return HIR "【 长  老 】" NOR;
                                                        if(budd >= 1000) return RED "【 堂  主 】" NOR;
                                                        if(budd >= 600) return RED "【 使  者 】" NOR;
                                                        if(budd >= 200) return CYN "【 教  徒 】" NOR;
                                                        return CYN "【 教  徒 】" NOR;
                                                case "欧阳世家":
                                                        if(budd >= 1900) return HIC "【西域魔王】" NOR;
                                                        if(budd >= 1500) return HIC "【 少庄主 】" NOR;
                                                        if(budd >= 1100) return HIC "【 教  练 】" NOR;
                                                        if(budd >= 700) return HIC "【 管  家 】" NOR;
                                                        if(budd >= 300) return HIC "【陪练童子】" NOR;
                                                        return HIC "【陪练童子】";
                                        } // switch(fname)
                                        if( !query("class", ob)){
                                                if (shen >= 1500000) return HIC "【武林神话】" NOR;
                                                if (shen >= 1000000) return HIC "【绝世神侠】" NOR;
                                                if (shen >= 500000) return HIC "【旷世大侠】" NOR;
                                                if (shen >= 50000) return HIC "【 大  侠 】" NOR;
                                                if (shen >= 5000) return HIC "【 侠  客 】" NOR;
                                                if (shen >= 500) return HIC "【 少  侠 】" NOR;
                                                if (shen <= -15000000) return HIB "【灭世魔尊】" NOR;
                                                if (shen <= -1000000) return HIB "【盖世狂魔】" NOR;
                                                if (shen <= -500000) return HIB "【 魔  尊 】" NOR;
                                                if (shen <= -50000) return HIB "【 魔  王 】" NOR;
                                                if (shen <= -5000) return HIB "【 魔  头 】" NOR;
                                                if (shen <= -500) return HIB "【 少  魔 】" NOR;
                                        }
                                        switch(query("class", ob)){
                                                case "bonze": return "【 僧  人 】";
                                                case "taoist":
                                                        if (budd >= 50 || age >= 20) return "【 道  士 】";
                                                        return "【 道  童 】";
                                                case "lama": return "【 喇  嘛 】";
                                                case "bandit": return "【 盗  贼 】";
                                                case "scholar": return "【 书  生 】";
                                                case "officer": return "【 官  差 】";
                                                case "fighter": return "【 武  者 】";
                                                case "swordsman": return "【 剑  士 】";
                                                case "alchemist": return "【 方  士 】";
                                                case "shaman": return "【 巫  医 】";
                                                case "beggar": return "【 叫化子 】";
                                                case "eunuch": return "【 太  监 】";
                                                default:
                                                        if( query("marry", ob)){
                                                                if (age < 30) return "【青年男子】";
                                                                if (age < 50) return "【中年男子】";
                                                                return "【 老头儿 】";
                                                        }
                                                        if (age < 18) return "【 少  年 】";
                                                        if (age < 30) return "【青年男子】";
                                                        if (age < 50) return "【中年男子】";
                                                        return "【 老处男 】";
                                        }//switch( query("class", ob) )
                        } // switch(wizhood(ob))
        }//switch( query("gender", ob) )
}

string query_respect(object ob)
{
        int age;
        string str;

        if (!ob) return "";
        if( stringp(str=query("rank_info/respect", ob)) )
                return str;

        age=query("age", ob);
        switch(query("gender", ob) )
        {
        case "女性":
                switch(query("class", ob) )
                {
                case "bonze":
                        if (age < 18) return "小师太";
                        else return "师太";
                        break;
                case "taoist":
                        if (age < 18) return "小仙姑";
                        else return "仙姑";
                        break;
                default:
                        if (age < 18) return "小姑娘";
                        else if (age < 30) return "姑娘";
                        else if (age < 40) return "大婶";
                        else return "婆婆";
                        break;
                }
        case "男性":
        default:
                switch(query("class", ob) )
                {
                case "bonze":
                        if (age < 18) return "小师父";
                        else return "大师";
                        break;
                case "taoist":
                        if (age < 18) return "道兄";
                        else return "道长";
                        break;
                case "scholar":
                        if (age < 18) return "小相公";
                        else if (age < 50) return "相公";
                        else return "老先生";
                        break;
                case "fighter":
                case "swordsman":
                        if (age < 18) return "小老弟";
                        else if (age < 50) return "壮士";
                        else return "老前辈";
                        break;
                default:
                        if (age < 20) return "小兄弟";
                        else if (age < 50) return "壮士";
                        else return "老爷子";
                        break;
                }
        }
}

string query_rude(object ob)
{
        int age;
        string str;

        if( stringp(str=query("rank_info/rude", ob)) )
                return str;

        age=query("age", ob);
        switch(query("gender", ob) )
        {
        case "女性":
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 18 ) return "小贼尼";
                        if( age < 30 ) return "贼尼";
                        else return "老贼尼";
                        break;
                case "taoist":
                        if( age < 18 ) return "小妖女";
                        if( age < 30 ) return "妖女";
                        else return "老妖婆";
                        break;
                default:
                        if( age < 18 ) return "小娘皮";
                        if( age < 25 ) return "小贱人";
                        if( age < 40 ) return "贼婆娘";
                        else return "死老太婆";
                        break;
                }
        case "男性":
        default:
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 18 ) return "小贼秃";
                        if( age < 50 ) return "死秃驴";
                        else return "老秃驴";
                        break;
                case "taoist":
                        if( age < 18 ) return "小杂毛";
                        if( age < 30 ) return "死牛鼻子";
                        else return "老杂毛";
                        break;
                case "scholar":
                        if( age < 18 ) return "小书呆子";
                        else if( age < 50 ) return "臭书呆子";
                        else return "老童生";
                        break;
                default:
                        if( age < 20 ) return "小王八蛋";
                        if( age < 30 ) return "直娘贼";
                        if( age < 50 ) return "臭贼";
                        if( age < 80 ) return "老匹夫";
                        else return "老不死";
                        break;
                }
        }
}

string query_self(object ob)
{
        int age;
        string str;

        if( stringp(str=query("rank_info/self", ob)) )
                return str;

        age=query("age", ob);
        switch(query("gender", ob) )
        {
        case "女性":
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 50 ) return "贫尼";
                        else return "老尼";
                        break;
                case "taoist":
                        return "贫道";
                        break;
                default:
                        if( age < 20 ) return "小女子";
                        if( age > 50 ) return "老身";
                        else return "妾身";
                        break;
                }
        case "男性":
        default:
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 18 ) return "小衲";
                        if( age < 40 ) return "贫僧";
                        else return "老衲";
                        break;
                case "taoist":
                        if( age < 18 ) return "小道";
                        if( age < 30 ) return "贫道";
                        else return "老道";
                        break;
                case "scholar":
                        if( age < 30 ) return "晚生";
                        else return "不才";
                        break;
                default:
                        if( age < 50 ) return "在下";
                        else return "老头子";
                        break;
                }
        }
}

string query_self_rude(object ob)
{
        int age;
        string str;

        if( stringp(str=query("rank_info/self_rude", ob)) )
                return str;

        age=query("age", ob);
        switch(query("gender", ob) )
        {
        case "女性":
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 50 ) return "贫尼";
                        else return "老尼";
                        break;
                case "taoist":
                        return "本仙姑";
                        break;
                default:
                        if( age < 20 ) return "本姑娘";
                        if( age < 30 ) return "本姑奶奶";
                        else return "老娘";
                        break;
                }
        case "男性":
        default:
                switch(query("class", ob) )
                {
                case "bonze":
                        if( age < 50 ) return "大和尚我";
                        else return "老和尚我";
                        break;
                case "taoist":
                        if( age < 30 ) return "本山人";
                        return "老道我";
                        break;
                case "scholar":
                        if( age < 50 ) return "本相公";
                        else return "老夫子我";
                        break;
                default:
                        if( age < 20 ) return "本少爷我";
                        if( age < 40 ) return "大爷我";
                        else return "老子";
                        break;
                }
        }
}

varargs string query_close(mixed ob, int a1, int a2)
{
        if (! a1 && this_player())
                a1=query("age", this_player());

        if (! a2 && objectp(ob))
                a2=query("age", ob);

        switch (objectp(ob) ? query("gender", ob) : ob)
        {
        case "女性":
                if (a1 >= a2)
                        return "妹妹";
                else
                        return "姐姐";
                break;

        default:
                if (a1 >= a2)
                        return "弟弟";
                else
                        return "哥哥";
        }
}

varargs string query_self_close(mixed ob, mixed me, int a1, int a2)
{
        if (! a1 && this_player())
                a1=query("age", this_player());

        if (! a2 && objectp(ob))
                a2=query("age", ob);

        switch (objectp(me) ? query("gender", me) :
                this_player() ? query("gender", this_player()) : me)
        {
        case "女性" :
                if (a1 >= a2)
                        return "姐姐我";
                else
                        return "小妹我";
                break;

        default :
                if (a1 >= a2)
                        return "愚兄我";
                else
                        return "小弟我";
        }
}

varargs string new_short(object ob, int withshort)
{
        mixed tmp;
        string icon = "", str;

        if (! objectp(ob))
        {
                CHANNEL_D->do_channel(this_player(), "chat", "object参数错误！");
                return "";
        }
        if( !query_temp("apply/id", ob) || !query_temp("apply/name", ob) || !query_temp("apply/short", ob) )
                str = query("name", ob) + "(" +query("id", ob) + ")" +(! withshort ? "" : ob->short());
        else
                str = query_temp("apply/name", ob)[0] + "(" +query_temp("apply/id", ob)[0] + ")" +
                        (! withshort ? "" : query_temp("apply/short", ob)[0]);
        if( (tmp=query("icon", ob)) )
        {
                if (intp(tmp))
                        icon = sprintf("%d", tmp);
                else if (stringp(tmp))
                        icon = tmp;
                else
                        icon = "00901";
        }
        else
        {
                if (userp(ob))
                        icon=(query("gender", ob) == "男性")?"1174":"1173";
                else
                if (living(ob))
                        icon = "00901";
                else icon = "00961";
        }
        while (sizeof(icon) < 5)
                icon = "0" + icon;

        return str + icon;
}