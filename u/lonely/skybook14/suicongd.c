// 随从系统，服务于14天书剧本

// #pragma optimize
// #pragma save_binary

#include <ansi.h>

inherit F_DBASE;

#define MEMBER_D           "/adm/daemons/memberd"
#define SUICONG_PATH       "SUICONG_LIST_TEST"
#define SUICONG_MAX_LEVEL  10
// 随从获得玩家体会分成比例
#define SLINE              "=--------------------------------------------------------------------------------------------------------------------="

// 随从升级需要的经验值
mapping SUICONG_LEVELUP = ([
"1" : 5000000,
"2" : 6000000,
"3" : 7000000,
"4" : 8000000,
"5" : 9000000,
"6" : 10000000,
"7" : 11000000,
"8" : 12000000,
"9" : 13000000,
"10": 2000000000,
]);


// 每部天书中 可获取的 随从列表
mapping SUICONG_LIST = ([
        "飞狐外传"    : ({"程灵素", "胡斐", "苗人凤","袁紫衣","田归农","商宝震","苗若兰","凤天南","无尘道长","李沅芷",}),

        "雪山飞狐"    : ({"曹云奇", "田青文", "平阿四","玄冥子","灵清道人","商剑鸣","李自成","杜希孟",   }),

        "连城诀"      : ({"狄云", "戚芳", "空心菜","凌退思","梅念笙","水笙","血刀老祖","宝象",  }),

        "天龙八部"    : ({"段誉", "段正淳", "段延庆","王语嫣","萧峰","萧远山","游坦之","完颜阿骨打","虚竹", "无涯子",
                          "天山童姥",  "李秋水",  "苏星河",  "丁春秋",  "慕容博",  "慕容复",
        }),

        "射雕英雄传"  : ({"郭靖", "黄蓉", "黄药师","杨铁心","杨康","江南七怪","洪七公","全真七子","周伯通","一灯大师", "傻姑", "郭啸天",
                          "梅超风","穆念慈","裘千仞","裘千丈","欧阳锋","欧阳克","黄河四鬼",
        }),

        "白马啸西风"  : ({"李文秀", "瓦尔拉齐", "上官虹","苏普","阿曼","苏鲁克","马家骏",  }),

        "鹿鼎记"      : ({"九难", "韦小宝","韦春花","归辛树","冯锡范","陈圆圆","吴三桂","陈近南","茅十八",
                          "瘦头陀", "胖头陀", "洪安通","海大富",
                          "双儿", "苏荃", "建宁公主","曾柔","阿珂","方怡","沐剑屏",
        }),

        "笑傲江湖"    : ({"不戒和尚", "木高峰", "风清扬","丛不弃","令狐冲","宁中则","平一指","东方不败","成不忧","冲虚道长",
                          "刘正风", "曲洋", "任盈盈","桃谷六仙","岳灵珊","林平之","蓝凤凰","岳不群","左冷禅","莫大", "向问天",
                          "任我行", "梅庄四杰",
        }),

        "书剑恩仇录"  : ({"心砚", "陈家洛","赵半山", "文泰来", "无尘道人","王维扬","李沅芷",
        }),

        "神雕侠侣"    : ({"小龙女", "冯默风", "瑛姑","张君宝","觉远大师","林朝英","忽必烈","金轮法王",
                          "杨过", "藏边五丑","陆无双","郭芙",
        }),

        "侠客行"      : ({"木岛主", "龙岛主", "丁珰","白自在","大悲老人","石破天","赏善罚恶使",
        }),

        "倚天屠龙记"  : ({"韦一笑", "明教五散人", "殷天正","黛绮丝","谢逊","阳顶天","何足道","杨不悔","武当七侠","周芷若",
                          "胡青牛", "赵敏", "郭襄","成昆","灭绝师太","张无忌","张三丰",
        }),

        "碧血剑"      : ({"何红药", "何铁手", "袁承志","温青","焦宛儿","黄真","归二娘", "木桑道长",  "玉真子",
        }),

        "鸳鸯刀"      : ({"逍遥子", "袁冠南", "盖一鸣","花剑影","林玉龙","卓天雄",
        }),
]);

// 对应不同的随从罗列其属性,修炼难度最低为1，最高为5
// 特殊效果用:分割，第1位代表保存在 set_temp()中的路径，2位代表初始1级随从的值，3位代表每次升级增加的值
//"狄云", "戚芳", "空心菜","丁典","凌退思","梅念笙","水笙","血刀老祖","宝象",
mapping SUICONG_LIST2 = ([

        "狄云"      : ([ "所属天书":"连城诀", "修炼难度":2, "特殊效果":"SKBSUICONG/jingli_limit:10:10", "效果描述": "增加精力上限10%～100%，每级增加10%"     ]),
        "宝象"      : ([ "所属天书":"连城诀", "修炼难度":1, "特殊效果":"SKBSUICONG/armor_add:10:10", "效果描述": "增加防御值10%～100%，每级增加10%"     ]),
        "水笙"      : ([ "所属天书":"连城诀", "修炼难度":2, "特殊效果":"SKBSUICONG/wound:1:1", "效果描述": "增加气血上限伤害1%～10%，每级增加1%"     ]),
        "梅念笙"    : ([ "所属天书":"连城诀", "修炼难度":3, "特殊效果":"SKBSUICONG/pot_add:1:1", "效果描述": "杀怪潜能加成1%～10%，每级增加1%"     ]),
        "血刀老祖"  : ([ "所属天书":"连城诀", "修炼难度":3, "特殊效果":"SKBSUICONG/xuedao-dafa:1:1", "效果描述": "血刀大法内力系数提升+6～15，每级+1；血刀大法绝招伤害大幅提升。"     ]),
        "凌退思"    : ([ "所属天书":"连城诀", "修炼难度":4, "特殊效果":"SKBSUICONG/armor_dec:2:2", "效果描述": "每次造成伤害可无视对方防御的2%～20%，每级增加2%"     ]),
        "戚芳"      : ([ "所属天书":"连城诀", "修炼难度":2, "特殊效果":"SKBSUICONG/hp_add:2:2", "效果描述": "气血上限提升2%～20%，每级增加2%"     ]),
        "空心菜"    : ([ "所属天书":"连城诀", "修炼难度":1, "特殊效果":"SKBSUICONG/int_add:1:1", "效果描述": "后天悟性+1～10，每级+1"     ]),
        "丁典"      : ([ "所属天书":"连城诀", "修炼难度":5, "特殊效果":"SKBSUICONG/shenzhao-jing:1:1", "效果描述": "神照经内力系数提升+1～10，每级+1；神照经绝招伤害大幅提升。"     ]),
]);

// 每本书有一名超级随从，其属性更好
mapping SUICONG_LIST3 = ([
        "飞狐外传"    : "无嗔",

        "雪山飞狐"    : "胡一刀",

        "连城诀"      : "丁典",

        "天龙八部"    : "扫地僧",

        "射雕英雄传"  : "黄裳",

        "白马啸西风"  : "高昌国王",

        "鹿鼎记"      : "康熙大帝",

        "笑傲江湖"    : "葵花太监",

        "书剑恩仇录"  : "阿凡提",

        "神雕侠侣"    : "独孤求败",

        "侠客行"      : "谢烟客",

        "倚天屠龙记"  : "霍山",

        "碧血剑"      : "穆人清",

        "鸳鸯刀"      : "萧中慧",

]);


/* 函数声明 */
int need_exp(string sName, string nLevel);

// 返回保存随从路径的字符串
string get_path(){return SUICONG_PATH;}

// 返回随从最大等级
int get_max_level(string sName){return SUICONG_MAX_LEVEL;}

// 计算当前随从升级所需的经验值，随从难度系数在原有基础上每点难度系数增加25%所需经验
int need_exp(string sName, int nLevel)
{
        int nDiff, nExp;
        mapping mSuicongInfo;

        mSuicongInfo = SUICONG_LIST2[sName];
        nDiff = mSuicongInfo["修炼难度"];

        nExp = SUICONG_LEVELUP[sprintf("%d",nLevel)];

        nExp = nExp + nExp / 100 * (nDiff*25);

        return nExp;
}

// 查看指定随从的详细属性
int show_suicong_target(object me, string sName)
{
        string sBook, sSkill, sMsg;
        int nDiff, nExp, nNeedExp;
        string *keys_suicong_list2;
        mapping mSuicongInfo, mySuicongInfo;

        keys_suicong_list2 = keys(SUICONG_LIST2);
        if (member_array(sName, keys_suicong_list2) == -1)
                return notify_fail("没有这个随从可查看！\n");

        mSuicongInfo = SUICONG_LIST2[sName];

        sBook = mSuicongInfo["所属天书"];
        sSkill = mSuicongInfo["效果描述"];
        nDiff = mSuicongInfo["修炼难度"];

        mySuicongInfo = me->query(SUICONG_PATH + "/" + sBook + "/" + sName);

        sMsg = HIC "查看随从【" + HIY + sName + HIC "】详细属性\n" NOR;
        sMsg+= SLINE + "\n";

        sMsg+= "所属天书：《" + sBook + "》\n" +
               "修炼难度：" + sprintf("%d", nDiff) + "（系数越高升级越慢）\n" +
               "当前等级：" + (mapp(mySuicongInfo) ? "Lv" + sprintf("%d", mySuicongInfo["level"]) : "未获得") + "\n" +
               ((mapp(mySuicongInfo) && mySuicongInfo["level"] >= SUICONG_MAX_LEVEL) ? "升级经验：" HIG "已满级" NOR:
               "升级经验：" + (mapp(mySuicongInfo) ? sprintf("%d/%d", mySuicongInfo["exp"], need_exp(sName,  mySuicongInfo["level"])) : "未获得") +
                              (mapp(mySuicongInfo) ? "(" + sprintf("%.1f", mySuicongInfo["exp"] * 100.0/need_exp(sName,  mySuicongInfo["level"]) ) + "%)":"")) + "\n"+
               "特殊效果：" + HIG +sSkill + "\n" NOR;
        sMsg+= SLINE + "\n";
        sMsg+= HIY "使用指令" HIM "suicong sum " + sName + HIY "可召唤该随从出来\n" NOR;

        write(sMsg);

        return 1;
}

// 获取随从的等级
public int GetLevel(object me, string sName)
{
        mapping mSuicongInfo, mySuicongInfo;
        string sBook;


        mSuicongInfo = SUICONG_LIST2[sName];

        sBook = mSuicongInfo["所属天书"];

        mySuicongInfo = me->query(SUICONG_PATH + "/" + sBook + "/" + sName);

        if (! mapp(mySuicongInfo))return 0;

        return mySuicongInfo["level"];
}

// 修改随从等级
public int AddLevel(object me, string sName, int nLevel)
{
        mapping mSuicongInfo, mySuicongInfo;
        string sBook;


        mSuicongInfo = SUICONG_LIST2[sName];

        sBook = mSuicongInfo["所属天书"];

        mySuicongInfo = me->query(SUICONG_PATH + "/" + sBook + "/" + sName);

        if (! mapp(mySuicongInfo))return 0;

        me->add(SUICONG_PATH + "/" + sBook + "/" + sName + "/level",nLevel );

        return 1;
}

// 获取随从经验
public int GetExp(object me, string sName)
{
        mapping mSuicongInfo, mySuicongInfo;
        string sBook;

        mSuicongInfo = SUICONG_LIST2[sName];

        sBook = mSuicongInfo["所属天书"];

        mySuicongInfo = me->query(SUICONG_PATH + "/" + sBook + "/" + sName);

        if (! mapp(mySuicongInfo))return 0;

        return mySuicongInfo["exp"];
}

// 修改随从经验
public int AddExp(object me, string sName, int nExp)
{
        mapping mSuicongInfo, mySuicongInfo;
        string sBook;


        mSuicongInfo = SUICONG_LIST2[sName];

        sBook = mSuicongInfo["所属天书"];

        mySuicongInfo = me->query(SUICONG_PATH + "/" + sBook + "/" + sName);

        if (! mapp(mySuicongInfo))return 0;

        me->add(SUICONG_PATH + "/" + sBook + "/" + sName + "/exp",nExp );

        return 1;
}


// 查看随从列表
int show_suicong(object me)
{
        int i,j,k,z;
        string *sBook, sSuicong, *sList;
        string sMsg;
        mapping mSuicongInfo;

        if (time() - me->query_temp("last_show_suicong") < 10)
                return notify_fail("10秒内只能查询一次随从！\n");

        me->set_temp("last_show_suicong", time());

        sBook = keys(SUICONG_LIST);
        sMsg = HIC "【十四天书随从】（排名不分先后）\n" NOR;
        k = 0; // 我总过多少名随从
        z = 0; // 总共开放多少名随从

        for (i = 0;i < sizeof(sBook);i ++)
        {
                sMsg+= SLINE + "\n";

                // 是否获得了超级随从
                if (! me->query(SUICONG_PATH + "/" + sBook[i] + "/" + SUICONG_LIST3[sBook[i]]))
                        sMsg += sprintf("%s（%s）\n", HIY "《" + sBook[i] + "》", "超级随从：" + NOR + WHT + SUICONG_LIST3[sBook[i]]+ HIY);
                else
                {
                        sMsg += sprintf("%s（%s）\n", HIY "《" + sBook[i] + "》", "超级随从：" + NOR + HIG + SUICONG_LIST3[sBook[i]] +
                                "（Lv" + sprintf("%d", me->query(SUICONG_PATH + "/" + sBook[i] + "/" + SUICONG_LIST3[sBook[i]] + "/level")) + "）" HIY );
                        k += 1;
                }

                sList = SUICONG_LIST[sBook[i]];

                for (j = 0; j < sizeof(sList); j ++)
                {
                        z += 1;
                        mSuicongInfo = me->query(SUICONG_PATH + "/" + sBook[i] + "/" + sList[j]);
                        if (! mSuicongInfo)
                        {
                                sMsg += sprintf( NOR + WHT "%-18s" NOR, sList[j]);
                        }
                        else
                        {
                                sMsg += sprintf(HIG "%-18s" NOR, sList[j]+ "（Lv" + sprintf("%d", mSuicongInfo["level"]) + "）"   );
                                k += 1;
                        }

                        if ((j+1)%6 == 0 && j != 0 && (j+1) != sizeof(sList))
                        {
                                sMsg += "\n";
                        }
                }
                sMsg += "\n";
        }
        sMsg+=  SLINE + "\n";
        sMsg += HIG "绿色代表你已经获取的随从  " NOR + WHT "灰色代表还没有获取的随从   " +
                HIY "你当前获得随从" + sprintf(HIR "%d/%d" HIY, k,z+14) + "名\n" NOR ;

        write(sMsg);

        return 1;
}

// 随从召唤
int summon_suicong(object me, string sName)
{
        mapping mSuicongInfo, mySuicongInfo;
        string sBook, *keys_suicong_list2;
        string sPerform, sPath;
        int nLevel, nInit, nAdd;

        keys_suicong_list2 = keys(SUICONG_LIST2);
        if (member_array(sName, keys_suicong_list2) == -1)
                return notify_fail("没有这个随从！\n");

        mSuicongInfo = SUICONG_LIST2[sName];

        sBook = mSuicongInfo["所属天书"];

        mySuicongInfo = me->query(SUICONG_PATH + "/" + sBook + "/" + sName);

        if (! mapp(mySuicongInfo))return notify_fail("你还没有获得" + HIG + sName + NOR "，请从" HIG + sBook + NOR "天书中获取！\n");

        // 先删除当期召唤的随从
        me->delete_temp(SUICONG_PATH + "/SUICONG");    // 删除当前召唤的随从
        me->delete_temp("SKBSUICONG"); // 删除随从的特效加成

        // 标注当前召唤的随从
        me->set_temp(SUICONG_PATH + "/SUICONG", sName);

        nLevel = mySuicongInfo["level"];

        // 设置随从特殊效果   特殊效果":"SKBSUICONG/shenzhao-jing:1:10
        sPerform = mSuicongInfo["特殊效果"];
        sscanf(sPerform, "%s:%d:%d", sPath, nInit, nAdd);
        me->set_temp(sPath, nInit + (nLevel-1)*nAdd); // 初始nInit,每级+nAdd

        message_vision(HIG "$N召唤出" HIY + sName + "\n" NOR, me);

        return 1;
}

// 返回当前召唤的随从的名字
string get_sum(object me)
{
        string sName;

        sName = me->query_temp(SUICONG_PATH + "/SUICONG");

        if (! sName)return "";

        return sName;
}

// 随从隐藏
int hide_suicong(object me)
{
        string sName;

        sName = me->query_temp(SUICONG_PATH + "/SUICONG");

        if (! sName)return notify_fail("你并没有召唤随从，无需收回！\n");

        message_vision(HIG "$N将" HIY + sName + HIG "收回。\n" NOR, me);

        me->delete_temp(SUICONG_PATH + "/SUICONG");
        me->delete_temp("SKBSUICONG"); // 删除随从的特效加成

        return 1;
}

// 获得一名随从
int give_suicong(object me, string sName)
{
        mapping mSuicongInfo, mySuicongInfo;
        string sBook, *keys_suicong_list2;

        keys_suicong_list2 = keys(SUICONG_LIST2);
        if (member_array(sName, keys_suicong_list2) == -1)
                return notify_fail("没有这个随从！\n");

        mSuicongInfo = SUICONG_LIST2[sName];

        sBook = mSuicongInfo["所属天书"];

        mySuicongInfo = me->query(SUICONG_PATH + "/" + sBook + "/" + sName);

        // 如果已经有这个随从则忽略
        if (mapp(mySuicongInfo))return 0;

        // 设置随从并初始化
        me->set(SUICONG_PATH + "/" + sBook + "/" + sName + "/level", 1);
        me->set(SUICONG_PATH + "/" + sBook + "/" + sName + "/exp", 100);

        return 1;
}


// 外部调用，随从获得经验
public void GiveExp(object me, int exp)
{
        string sName;
        int nLevel;
        // 如果当前有召唤并且没有满级
        sName = me->query_temp(SUICONG_PATH + "/SUICONG");

        if (sizeof(sName))
        {
                nLevel = GetLevel(me, sName);
                if (nLevel >= SUICONG_MAX_LEVEL)return;

                AddExp(me, sName, exp);

                // 如果达到升级经验则升级
                if (GetExp(me, sName) >= need_exp(sName, nLevel))
                {
                        AddLevel(me, sName, 1);
                        AddExp(me, sName, -1 * need_exp(sName, nLevel));
                        tell_object(me, HIG "你的随从" HIY + sName + HIG "等级提升到" HIY + sprintf("%d", nLevel+1) + HIG "级。\n" NOR);

                        if (nLevel+1 >= SUICONG_MAX_LEVEL)
                                AddExp(me ,sName, -1 * GetExp(me, sName));
                }


        }
}

// 测试
public void testgiveexp()
{
        GiveExp(this_player(), 1000000);
}

void create()
{
        seteuid(getuid());
}
