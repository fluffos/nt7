//对应武器数据表
mapping weapon_file =
([
    "sword" : "/clone/weapon/gangjian",   //钢剑
    "blade" : "/clone/weapon/gangdao",    //钢刀
    "dadao" : "/clone/weapon/dadao",      //大刀
    "staff" : "/clone/weapon/gangzhang",  //钢杖
    "qiang" : "/clone/weapon/changqiang", //长枪
    "axe"   : "/clone/weapon/tiefu",      //铁斧
    "fork"  : "/clone/weapon/gangcha",    //钢叉
    "whip"  : "/clone/weapon/changbian",  //长鞭
    "wodao" : "/clone/weapon/wodao",      //倭刀
    "xiyang-jian" : "/clone/weapon/xiyang-jian",    //西洋剑
]);

//技能名称对照表
mapping weapon_type =
([
    "axe"     : "斧法",
    "blade"   : "刀法",
    "claw"    : "爪法",
    "dadao"   : "刀法",
    "fork"    : "叉法",
    "finger"  : "指法",
    "qiang"   : "枪法",
    "staff"   : "杖法",
    "sword"   : "剑法",
    "unarmed" : "拳法",
    "whip"    : "鞭法",
]);

//技能情况数据表
mapping *all_skill = ({
([
    "faction" : "白驼",             //所属门派
    "name"    : "灵蛇杖法",         //技能名称
    "code"    : "baituo_1",         //技能代号
    "weapon"  : "staff",            //武器类型
    "gender"  : "all",              //性别限制
    "horse"   : 0,                  //马术需求
    "m_skill" : ([                  //技能映射
                    "unarmed" : "shexing-diaoshou",
                    "dodge"   : "chanchu-bufa",
                    "parry"   : "lingshe-zhangfa",
                    "staff"   : "lingshe-zhangfa",
                    "force"   : "hamagong",
                ]),
    "p_skill" : ([]),               //预备技能
    "special" : ([                  //特殊标记
                    "weapon/she" :  30,
                    "weapon/id"  : "gang zhang",
                ]),
]),
([
    "faction" : "峨嵋",
    "name"    : "回风拂柳剑",
    "code"    : "emei_1",
    "weapon"  : "sword",
    "gender"  : "female",
    "m_skill" : ([
                    "force"   : "jiuyin-shengong",
                    "sword"   : "huifeng-jian",
                    "parry"   : "huifeng-jian",
                    "unarmed" : "piaoxue-zhang",
                    "claw"    : "jieshou-jiushi",
                    "dodge"   : "anying-fuxiang",
                ]),
    "p_skill" : ([
                    "unarmed" : "piaoxue-zhang",
                    "claw"    : "jieshou-jiushi",
                ]),
]),
([
    "faction" : "峨嵋",
    "name"    : "九阴摧心爪",
    "code"    : "emei_2",
    "weapon"  : "claw",
    "gender"  : "female",
    "m_skill" : ([
                    "force"   : "jiuyin-shengong",
                    "parry"   : "jiuyin-baiguzhao",
                    "claw"    : "jiuyin-baiguzhao",
                    "dodge"   : "anying-fuxiang",
                ]),
    "p_skill" : ([
                    "claw"    : "jiuyin-baiguzhao",
                ]),
]),
([
    "faction" : "丐帮",
    "name"    : "降龙十八掌",
    "code"    : "gaibang_1",
    "weapon"  : "unarmed",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "xianglong-zhang",
                    "dodge"   : "xiaoyaoyou",
                    "parry"   : "xianglong-zhang",
                    "force"   : "huntian-qigong",
                ]),
]),
([
    "faction" : "丐帮",
    "name"    : "打狗棒法",
    "code"    : "gaibang_2",
    "weapon"  : "staff",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "xianglong-zhang",
                    "dodge"   : "xiaoyaoyou",
                    "parry"   : "dagou-bang",
                    "staff"   : "dagou-bang",
                    "force"   : "huntian-qigong",
                ]),
]),
([
    "faction" : "华山",
    "name"    : "华山剑法",
    "code"    : "huashan_1",
    "weapon"  : "sword",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "hunyuan-zhang",
                    "dodge"   : "huashan-shenfa",
                    "parry"   : "huashan-jianfa",
                    "sword"   : "huashan-jianfa",
                    "force"   : "zixia-shengong",
                ]),
    "special" : ([
                    "huashan_marks/ningshi" : 1,
                ]),
]),
([
    "faction" : "华山",
    "name"    : "两仪刀法",
    "code"    : "huashan_2",
    "weapon"  : "blade",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "hunyuan-zhang",
                    "dodge"   : "huashan-shenfa",
                    "parry"   : "liangyi-daofa",
                    "blade"   : "liangyi-daofa",
                    "force"   : "zixia-shengong",
                ]),
]),
([
    "faction" : "昆仑",
    "name"    : "两仪剑法",
    "code"    : "kunlun_1",
    "weapon"  : "sword",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "kunlun-zhang",
                    "dodge"   : "yingxian-bu",
                    "parry"   : "liangyi-jian",
                    "sword"   : "liangyi-jian",
                    "force"   : "jingshen-jue",
                ]),
]),
([
    "faction" : "灵鹫",
    "name"    : "天羽奇剑",
    "code"    : "lingjiu_1",
    "weapon"  : "sword",
    "gender"  : "female",
    "m_skill" : ([
                    "claw"    : "zhemei-shou",
                    "dodge"   : "yueying-wubu",
                    "parry"   : "tianyu-qijian",
                    "sword"   : "tianyu-qijian",
                    "force"   : "bahuang-gong",
                ]),
    "p_skill" : ([
                    "claw"    : "zhemei-shou",
                ]),
]),
([
    "faction" : "青城",
    "name"    : "松风剑法",
    "code"    : "qingcheng_1",
    "weapon"  : "sword",
    "gender"  : "male",
    "m_skill" : ([
                    "unarmed" : "cuixin-zhang",
                    "dodge"   : "chonghe-bufa",
                    "parry"   : "songfeng-jianfa",
                    "sword"   : "songfeng-jianfa",
                    "force"   : "qingcheng-xinfa",
                ]),
]),
([
    "faction" : "全真",
    "name"    : "全真剑法",
    "code"    : "quanzhen_1",
    "weapon"  : "sword",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed"  : "sanhua-judingzhang",
                    "dodge"    : "jinyan-gong",
                    "parry"    : "quanzhen-jianfa",
                    "sword"    : "quanzhen-jianfa",
                    "force"    : "xuanmen-neigong",
                ]),
]),
([
    "faction" : "少林",
    "name"    : "达摩剑法",
    "code"    : "shaolin_1",
    "weapon"  : "sword",
    "gender"  : "male",
    "m_skill" : ([
                    "finger"  : "nianhua-zhi",
                    "dodge"   : "shaolin-shenfa",
                    "parry"   : "damo-jian",
                    "sword"   : "damo-jian",
                    "force"   : "hunyuan-yiqi",
                ]),
    "p_skill" : ([
                    "finger"  : "nianhua-zhi",
                ]),
]),
([
    "faction" : "少林",
    "name"    : "拈花指法",
    "code"    : "shaolin_2",
    "weapon"  : "finger",
    "gender"  : "male",
    "m_skill" : ([
                    "dodge"   : "shaolin-shenfa",
                    "parry"   : "nianhua-zhi",
                    "finger"  : "nianhua-zhi",
                    "force"   : "hunyuan-yiqi",
                ]),
    "p_skill" : ([
                    "finger"  : "nianhua-zhi",
                ]),
    "special" : ([]),
]),
([
    "faction" : "少林",
    "name"    : "日月鞭法",
    "code"    : "shaolin_3",
    "weapon"  : "whip",
    "gender"  : "male",
    "m_skill" : ([
                    "finger"  : "nianhua-zhi",
                    "dodge"   : "shaolin-shenfa",
                    "parry"   : "riyue-bian",
                    "whip"    : "riyue-bian",
                    "force"   : "hunyuan-yiqi",
                ]),
    "p_skill" : ([
                    "finger"  : "nianhua-zhi",
                ]),
]),
([
    "faction" : "神龙",
    "name"    : "蛇岛奇剑",
    "code"    : "shenlong_1",
    "weapon"  : "sword",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed"  : "shenlong-bashi",
                    "dodge"    : "yixingbu",
                    "parry"    : "shedao-qijian",
                    "sword"    : "shedao-qijian",
                    "force"    : "shenlong-zhanqi",
                ]),
]),
([
    "faction" : "神龙",
    "name"    : "神龙八式",
    "code"    : "shenlong_2",
    "weapon"  : "unarmed",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed"  : "shenlong-bashi",
                    "parry"    : "shenlong-bashi",
                    "dodge"    : "yixingbu",
                    "force"    : "shenlong-zhanqi",
                ]),
]),
([
    "faction" : "桃花",
    "name"    : "落英神剑",
    "code"    : "taohua_1",
    "weapon"  : "sword",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed"  : "luoying-zhang",
                    "dodge"    : "anying-fuxiang",
                    "parry"    : "luoying-shenjian",
                    "sword"    : "luoying-shenjian",
                    "force"    : "bibo-shengong",
                ]),
]),
([
    "faction" : "桃花",
    "name"    : "九阴白骨爪",
    "code"    : "taohua_2",
    "weapon"  : "claw",
    "gender"  : "all",
    "m_skill" : ([
                    "claw"    : "jiuyin-baiguzhao",
                    "dodge"   : "anying-fuxiang",
                    "parry"   : "jiuyin-baiguzhao",
                    "force"   : "bibo-shengong",
                ]),
    "p_skill" : ([
                    "claw"    : "jiuyin-baiguzhao",
                ]),
]),
([
    "faction" : "武当",
    "name"    : "太极剑法",
    "code"    : "wudang_1",
    "weapon"  : "sword",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "taiji-quan",
                    "dodge"   : "tiyunzong",
                    "parry"   : "taiji-jian",
                    "sword"   : "taiji-jian",
                    "force"   : "taiji-shengong",
                ]),
]),
([
    "faction" : "武官",
    "name"    : "杨家枪法",
    "code"    : "wuguan_1",
    "weapon"  : "qiang",
    "gender"  : "all",
    "horse"   : 1,
    "m_skill" : ([
                    "unarmed" : "taizu-changquan",
                    "dodge"   : "tianma-xingkong",
                    "parry"   : "yangjia-qiang",
                    "qiang"   : "yangjia-qiang",
                    "force"   : "longhu-baqi",
                ]),
]),
([
    "faction" : "武官",
    "name"    : "春秋大刀",
    "code"    : "wuguan_2",
    "weapon"  : "dadao",
    "gender"  : "all",
    "horse"   : 1,
    "m_skill" : ([
                    "unarmed" : "taizu-changquan",
                    "dodge"   : "tianma-xingkong",
                    "parry"   : "chunqiu-dadao",
                    "blade"   : "chunqiu-dadao",
                    "force"   : "longhu-baqi",
                ]),
]),
([
    "faction" : "武官",
    "name"    : "托天叉法",
    "code"    : "wuguan_3",
    "weapon"  : "fork",
    "gender"  : "all",
    "horse"   : 1,
    "m_skill" : ([
                    "unarmed" : "taizu-changquan",
                    "dodge"   : "tianma-xingkong",
                    "fork"    : "tuotian-cha",
                    "parry"   : "tuotian-cha",
                    "force"   : "longhu-baqi",
                ]),
]),
([
    "faction" : "武官",
    "name"    : "风魔斧法",
    "code"    : "wuguan_4",
    "weapon"  : "axe",
    "gender"  : "all",
    "horse"   : 1,
    "m_skill" : ([
                    "unarmed" : "taizu-changquan",
                    "dodge"   : "tianma-xingkong",
                    "parry"   : "fengmo-fu",
                    "axe"     : "fengmo-fu",
                    "force"   : "longhu-baqi",
                ]),
]),
([
    "faction" : "云龙",
    "name"    : "云龙剑法",
    "code"    : "yunlong_1",
    "weapon"  : "sword",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "yunlong-shou",
                    "claw"    : "yunlong-zhua",
                    "dodge"   : "yunlong-shenfa",
                    "parry"   : "yunlong-jian",
                    "sword"   : "yunlong-jian",
                    "force"   : "yunlong-shengong",
                ]),
    "p_skill" : ([
                    "claw"    : "yunlong-zhua",
                    "unarmed" : "yunlong-shou",
                ]),
]),
([
    "faction" : "云龙",
    "name"    : "云龙鞭法",
    "code"    : "yunlong_2",
    "weapon"  : "whip",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "yunlong-shou",
                    "claw"    : "yunlong-zhua",
                    "dodge"   : "yunlong-shenfa",
                    "parry"   : "yunlong-bian",
                    "whip"    : "yunlong-bian",
                    "force"   : "yunlong-shengong",
                ]),
    "p_skill" : ([
                    "claw"    : "yunlong-zhua",
                    "unarmed" : "yunlong-shou",
                ]),
]),
([
    "faction" : "云龙",
    "name"    : "五虎断门刀",
    "code"    : "yunlong_3",
    "weapon"  : "blade",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "yunlong-shou",
                    "claw"    : "yunlong-zhua",
                    "dodge"   :"yunlong-shenfa",
                    "parry"   : "wuhu-duanmendao",
                    "blade"   : "wuhu-duanmendao",
                    "force"   : "yunlong-shengong",
                ]),
    "p_skill" : ([
                    "claw"    : "yunlong-zhua",
                    "unarmed" : "yunlong-shou",
                ]),
]),
([
    "faction" : "云龙",
    "name"    : "凝血神抓",
    "code"    : "yunlong_4",
    "weapon"  : "claw",
    "gender"  : "all",
    "m_skill" : ([
                    "unarmed" : "yunlong-shou",
                    "claw"    : "yunlong-zhua",
                    "dodge"   : "yunlong-shenfa",
                    "parry"   : "yunlong-shou",
                    "force"   : "yunlong-shengong",
                ]),
    "p_skill" : ([
                    "claw"    : "yunlong-zhua",
                    "unarmed" : "yunlong-shou",
                ]),
]),
([
    "faction" : "倭寇",
    "name"    : "东瀛忍术",
    "code"    : "wokou",
    "weapon"  : "wodao",
    "gender"  : "male",
    "nation"  : "日本",
    "no_list" : 1,
    "m_skill" : ([
                    "blade"   : "wo-dao",
                    "unarmed" : "dongying-renshu",
                    "dodge"   : "dongying-renshu",
                    "parry"   : "wo-dao",
                    "force"   : "jidao-shaqi",
                ]),
]),
([
    "faction" : "西洋",
    "name"    : "西洋搏击",
    "code"    : "xiyang",
    "weapon"  : "xiyang-jian",
    "gender"  : "male",
    "nation"  : "欧洲",
    "no_list" : 1,
    "m_skill" : ([
                    "sword"   : "xiyang-jian",
                    "unarmed" : "xiyang-boji",
                    "dodge"   : "xiyang-boji",
                    "parry"   : "xiyang-jian",
                    "force"   : "jidao-shaqi",
                ]),
]),
([
    "faction" : "巡捕",
    "name"    : "呼卢喝雉手",
    "code"    : "butou",
    "weapon"  : "unarmed",
    "gender"  : "male",
    "no_list" : 1,
    "m_skill" : ([
                    "unarmed" : "huluhezhi-shou",
                    "dodge"   : "yixingbu",
                    "parry"   : "huluhezhi-shou",
                    "force"   : "hujiahuwei-gong",
                ]),
]),
});
