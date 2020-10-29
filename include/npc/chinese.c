// chinese name

#include "name.h"

mapping get_cn_name();
mapping cn_sname = ([
//中华单姓
        "赵" : "zhao",
        "钱" : "qian",
        "孙" : "sun",
        "李" : "li",
        "周" : "zhou",
        "吴" : "wu",
        "郑" : "zheng",
        "王" : "wang",
        "冯" : "feng",
        "陈" : "chen",
        "褚" : "chu",
        "卫" : "wei",
        "蒋" : "jiang",
        "沈" : "shen",
        "韩" : "han",
        "杨" : "yang",
        "朱" : "zhu",
        "秦" : "qin",
        "尤" : "you",
        "许" : "xu",
        "何" : "he",
        "吕" : "lv",
        "施" : "shi",
        "张" : "zhang",
        "孔" : "kong",
        "曹" : "cao",
        "严" : "yan",
        "华" : "hua",
        "金" : "jin",
        "魏" : "wei",
        "陶" : "tao",
        "姜" : "jiang",
        "戚" : "qi",
        "谢" : "xie",
        "邹" : "zou",
        "喻" : "yu",
        "柏" : "bo",
        "水" : "shui",
        "窦" : "dou",
        "章" : "zhang",
        "云" : "yun",
        "苏" : "su",
        "潘" : "pan",
        "葛" : "ge",
        "奚" : "xi",
        "范" : "fan",
        "彭" : "peng",
        "郎" : "lang",
        "鲁" : "lu",
        "韦" : "wei",
        "马" : "ma",
        "苗" : "miao",
        "凤" : "feng",
        "花" : "hua",
        "方" : "fang",
        "任" : "ren",
        "袁" : "yuan",
        "柳" : "liu",
        "邓" : "deng",
        "鲍" : "bao",
        "史" : "shi",
        "唐" : "tang",
        "费" : "fei",
        "廉" : "lian",
        "岑" : "cen",
        "薛" : "xue",
        "雷" : "lei",
        "贺" : "he",
        "倪" : "ni",
        "汤" : "tang",
        "藤" : "teng",
        "殷" : "yin",
        "罗" : "luo",
        "华" : "hua",
        "郝" : "hao",
        "邬" : "wu",
        "安" : "an",
        "常" : "chang",
        "乐" : "le",
        "时" : "shi",
        "付" : "fu",
        "皮" : "pi",
        "卞" : "bian",
        "齐" : "qi",
        "康" : "kang",
        "伍" : "wu",
        "余" : "yu",
        "元" : "yuan",
        "卜" : "bu",
        "顾" : "gu",
        "平" : "ping",
        "黄" : "huang",
        "和" : "he",
        "穆" : "mu",
        "肖" : "xiao",
        "尹" : "yin",
        "姚" : "yao",
        "邵" : "shao",
        "汪" : "wang",
        "祁" : "qi",
        "毛" : "mao",
        "禹" : "yu",
        "狄" : "di",
        "米" : "mi",
        "贝" : "bei",
        "明" : "ming",
        "计" : "ji",
        "伏" : "fu",
        "成" : "cheng",
        "戴" : "dai",
        "谈" : "tan",
        "宋" : "song",
        "茅" : "mao",
        "庞" : "pang",
        "熊" : "xiong",
        "纪" : "ji",
        "舒" : "shu",
        "屈" : "qu",
        "项" : "xiang",
        "祝" : "zhu",
        "董" : "dong",
        "梁" : "liang",
        "樊" : "fan",
        "胡" : "hu",
        "凌" : "ling",
        "霍" : "huo",
        "虞" : "yu",
        "万" : "wan",
        "支" : "zhi",
        "柯" : "ke",
        "昝" : "jiu",
        "管" : "guan",
        "卢" : "lu",
        "英" : "ying",
        "仇" : "qiu",
        "侯" : "hou",
        "岳" : "yue",
        "帅" : "shuai",
        "宁" : "ning",
        "谷" : "gu",
        "楚" : "chu",
        "晋" : "jin",
        "阎" : "yan",
        "法" : "fa",
        "鄢" : "yan",
        "涂" : "tu",
        "钦" : "qin",
        "段" : "duan",
        "归" : "gui",
        "海" : "hai",
        "况" : "kuang",
        "琴" : "qin",
        "商" : "shang",
        "牟" : "mou",
        "佘" : "she",
        "墨" : "mo",
        "哈" : "ha",
        "年" : "nian",
        "阳" : "yang",
        "佟" : "tong",
        "言" : "yan",
        "蒯" : "kuai",
        "钟" : "zhong",
        "宗" : "zong",
        "林" : "lin",
        "石" : "shi",
        "刘" : "liu",
        "徐" : "xu",
        "郭" : "guo",
        "萧" : "xiao",
        "程" : "cheng",
        "傅" : "fu",
        "曾" : "zeng",
        "蔡" : "cai",
        "贾" : "jia",
        "丁" : "ding",
        "叶" : "ye",
        "杜" : "du",
        "夏" : "xia",
        "田" : "tian",
        "谭" : "tan",
        "廖" : "liao",
        "陆" : "lu",
        "白" : "bai",
        "崔" : "cui",
        "邱" : "qiu",
        "江" : "jiang",
        "史" : "shi",
        "侯" : "hou",
        "孟" : "meng",
        "龙" : "long",
        "黎" : "li",
        "易" : "yi",
        "武" : "wu",
        "乔" : "qiao",
        "赖" : "lai",
        "龚" : "gong",
        "文" : "wen",

//中华复姓
        "东方" : "dongfang",
        "独孤" : "dugu",
        "慕容" : "murong",
        "欧阳" : "ouyang",
        "司马" : "sima",
        "西门" : "ximen",
        "尉迟" : "yuchi",
        "长孙" : "zhangsun",
        "诸葛" : "zhuge",
        "上官" : "shangguan",
        "夏侯" : "xiahou",
        "闻人" : "wenren",
        "皇甫" : "huangfu",
        "澹台" : "tantai",
        "公治" : "gongzhi",
        "淳于" : "chunyu",
        "申屠" : "shentu",
        "公孙" : "gongsun",
        "公羊" : "gongyang",
        "轩辕" : "xuanyuan",
        "令狐" : "linghu",
        "钟离" : "zhongli",
        "宇文" : "yuwen",
        "慕容" : "murong",
        "仲孙" : "zhongsun",
        "司徒" : "situ",
        "司空" : "sikong",
        "端木" : "duanmu",
        "公良" : "gongliang",
        "百里" : "baili",
        "东郭" : "dongguo",
        "鲜于" : "xianyu",
        "南郭" : "nanguo",
        "呼延" : "huyan",
        "羊舌" : "yangshe",
        "东门" : "dongmen",
        "纳兰" : "nalan",
        "南官" : "nanguan",
        "南宫" : "nangong",
        "拓拔" : "tuoba",
        "完颜" : "wanyan",
        "耶律" : "yelv",
]);

mapping cn_pname = ([
        "a"    : "阿",
        "ai"   : "皑艾哀蔼隘埃瑷嫒捱",
        "an"   : "安黯谙岸鞍埯鹌",
        "ao"   : "奥傲敖骜翱鳌",
        "ang"  : "昂盎肮",
        "ba"   : "罢霸跋魃",
        "bai"  : "白佰",
        "ban"  : "班斑般",
        "bang" : "邦",
        "bei"  : "北倍贝备",
        "biao" : "表标彪飚飙",
        "bian" : "边卞弁忭",
        "bin"  : "斌宾彬",
        "bing" : "并兵丙秉炳禀",
        "bu"   : "步不部布埠",
        "cao"  : "曹草操漕",
        "cai"  : "才采材财",
        "cang" : "苍仓沧伧",
        "chang": "长昌敞玚厂畅昶",
        "chao" : "超潮巢朝",
        "chen" : "辰臣尘晨沉嗔宸伧",
        "cheng": "诚呈丞承骋埕铖澄晟",
        "chi"  : "迟持池赤尺驰炽",
        "chuan": "川舛传遄",
        "ci"   : "此次词茨辞赐祠兹",
        "da"   : "大达",
        "de"   : "德得",
        "ding" : "鼎定碇酊町铤",
        "du"   : "独都度督笃",
        "dong" : "东侗栋鸫峒",
        "dou"  : "斗兜窦",
        "duo"  : "多夺舵踱",
        "fa"   : "法发乏珐筏伐",
        "fan"  : "凡反泛帆蕃繁藩梵",
        "fang" : "方访邡昉仿坊",
        "fei"  : "飞芾斐",
        "feng" : "风凤封丰奉枫峰锋",
        "fu"   : "福夫符弗芙",
        "gao"  : "高皋郜镐稿诰缟杲",
        "gang" : "钢罡刚纲岗冈",
        "gong" : "公工宫功恭觥",
        "guan" : "贯官灌冠纶",
        "guang": "光广",
        "hai"  : "海亥",
        "hao"  : "号浩皓蒿浩昊灏淏",
        "hong" : "洪红宏鸿虹泓弘",
        "hu"   : "虎忽湖护乎祜浒怙",
        "hua"  : "化华骅桦画",
        "ji"   : "积极济技击疾及基集记纪季继吉计冀祭际籍绩忌寂霁稷玑芨蓟戢佶奇诘笈畿犄",
        "jin"  : "金进今近锦津堇瑾",
        "jing" : "竟静惊经镜京净敬精景警竞境径荆兢靖旌劲",
        "jian" : "渐剑见建间柬坚俭健",
        "jiang": "将疆洚缰",
        "jie"  : "杰节界皆阶介届芥捷颉",
        "jun"  : "俊君均峻竣骏钧筠",
        "kan"  : "刊戡坎莰",
        "kang" : "康慷亢",
        "ke"   : "可克科刻珂恪溘牁",
        "kuang": "匡旷",
        "lang" : "朗浪廊琅阆莨",
        "li"   : "历离里理利立力丽礼黎栗荔沥栎璃",
        "lian" : "连联练炼敛廉涟濂",
        "liang": "良亮凉量谅莨",
        "lin"  : "临霖麟",
        "ling" : "令岭陵龄凌棱",
        "lu"   : "禄路鲁录庐麓泸簏碌",
        "mao"  : "贸冒貌冒懋矛卯瑁",
        "miao" : "淼渺邈",
        "ming" : "明铭鸣",
        "nan"  : "楠南",
        "ning" : "宁泞甯",
        "pian" : "片翩",
        "pin"  : "品",
        "pei"  : "培佩沛辔旆锫霈",
        "qi"   : "启其器奇岂弃企契歧祈栖崎旗蕲杞耆憩麒圻",
        "qian" : "潜谦倩茜乾虔千",
        "qiang": "强羌锖玱",
        "qin"  : "钦矜",
        "qing" : "清庆卿晴",
        "qu"   : "驱取渠劬麴趋",
        "ran"  : "冉然染燃",
        "ren"  : "人仁刃壬仞韧衽",
        "rong" : "荣容熔戎冗嵘榕肜",
        "ruo"  : "若箬",
        "sha"  : "沙煞刹霎",
        "shan" : "山善杉陕埏",
        "shang": "上商尚殇",
        "shen" : "深审神申慎参莘",
        "shi"  : "师史石时十世士诗始示适炻",
        "shu"  : "叔树书术束述枢殊曙庶戍蜀黍墅恕澍",
        "shui" : "水",
        "si"   : "思斯丝司祀嗣巳",
        "song" : "松颂诵崧嵩淞竦",
        "tai"  : "泰太台骀薹",
        "tang" : "堂棠瑭",
        "tao"  : "涛淘滔韬焘",
        "tong" : "统通同童彤仝",
        "tian" : "天忝阗",
        "tie"  : "铁帖",
        "ting" : "挺庭停听厅廷霆铤",
        "wan"  : "宛晚挽皖芄",
        "wei"  : "卫微伟维威韦纬炜惟玮为",
        "wen"  : "文紊",
        "wu"   : "吴物务武午五巫邬兀毋戊",
        "xi"   : "西席锡熙洗夕兮熹惜",
        "xiao" : "小孝潇笑晓肖霄骁校",
        "xian" : "宪显闲献贤",
        "xiang": "祥相巷翔详襄骧",
        "xiong": "熊芎雄",
        "xu"   : "旭须虚序戌绪诩勖煦胥",
        "xue"  : "学泶",
        "yang" : "羊洋阳漾央秧炀飏鸯",
        "yi"   : "义易意依亦伊夷倚毅义宜仪艺译翼逸忆怡熠沂颐奕弈懿翊轶屹猗翌",
        "yin"  : "隐因引银音寅吟胤訚烟荫",
        "ying" : "映英影颖瑛应莹郢鹰",
        "you"  : "友幽悠右忧猷酉",
        "yong" : "勇永",
        "yu"   : "渔郁寓玉雨语预羽舆育宇禹域誉瑜屿御渝毓虞禺豫裕钰煜聿",
        "zhi"  : "之制至值知质致智志直治执止置芝旨峙芷挚郅炙雉帜",
        "zhong": "中忠钟衷",
        "zhou" : "州舟胄繇昼",
        "zhu"  : "竹驻诸著竺",
        "zhuo" : "灼灼拙琢濯斫擢焯酌",
        "zi"   : "自子资兹紫姿孜梓秭",
        "zong" : "宗枞",
        "zu"   : "足族祖卒",
        "zuo"  : "作左佐笮凿",
]);

//中华女名（今后继续添加，以丰富变化）
mapping cn_pwname = ([
        "ai"   : "爱嫒瑷",
        "bin"  : "鬓玢",
        "chun" : "春纯莼",
        "dan"  : "丹萏",
        "fang" : "芳",
        "fei"  : "菲妃翡霏",
        "fen"  : "纷芬玢馚",
        "feng" : "凤枫",
        "hong" : "红虹荭泓",
        "jiao" : "娇姣皎",
        "juan" : "娟鹃绢涓",
        "ju"   : "菊",
        "ke"   : "可珂",
        "lan"  : "兰岚蓝澜斓",
        "li"   : "丽莉梨黎荔俪俐藜",
        "lian" : "莲怜",
        "ling" : "玲琳铃灵菱凌羚苓绫翎",
        "man"  : "曼蔓缦",
        "mei"  : "媚妹美玫莓湄",
        "na"   : "娜纳",
        "qi"   : "琪琦",
        "qin"  : "琴芹沁芩衾",
        "qian" : "倩纤芊褰茜",
        "qing" : "青清卿",
        "ping" : "萍苹娉",
        "rou"  : "柔",
        "ting" : "婷葶",
        "wen"  : "雯纹璺",
        "xia"  : "霞瑕",
        "xian" : "仙",
        "xiang": "香湘襄缃",
        "xin"  : "馨欣",
        "xiu"  : "绣袖秀",
        "xue"  : "雪",
        "yan"  : "艳燕烟滟妍嫣琰胭芫",
        "ying" : "英瑛颖莺萦璎荧",
        "yu"   : "玉妤瑜",
        "yue"  : "月",
        "zhen" : "珍真贞箴",
        "zhu"  : "珠",
]);

string make_cn_name()
{
        string *ks_cn_sname, *ks_cn_pname;
        string fir_name, sec_name, result_name;
//      int iname;

        string *new_sname;
        string *new_pname;

        new_sname = ({
                "或", "和", "与", "加", "减", "乘", "除", "开", "当", "更", "天下", "炎黄",
                "反贼", "至尊", "修身", "司徒", "白玉", "惊蛰",
        });

        new_pname = ({
                "或", "业", "野", "系", "盗贼", "匹夫", "败类", "老贼",
        });

        ks_cn_sname = keys(cn_sname);
        ks_cn_pname = keys(cn_pname);

        // 30%用新的姓
        if (random(10) < 3)
                fir_name = new_sname[random(sizeof(new_sname))];
        else
                fir_name = ks_cn_sname[random(sizeof(ks_cn_sname))]; // 姓

        // 名
        // 30%用新的名
        if (random(10) < 3)
                sec_name = new_pname[random(sizeof(new_pname))];
        else
        {
                sec_name = ks_cn_pname[random(sizeof(ks_cn_pname))];
                sec_name = cn_pname[sec_name];
                sec_name = sec_name[(random(sizeof(sec_name)) & 0xFFFE)..<1];
                sec_name = sec_name[0..1];
        }

        // 1/10 几率用数字中文代替
        if (random(10) == 1)
        {
                sec_name = chinese_number(random(100));
        }

        result_name = fir_name + sec_name;

        return result_name;
}

void generate_cn_name(object ob)
{
        string sname, pname, pname2, id1, id2;
        string *ks, *kp;

        ks = keys(cn_sname);
        kp = keys(cn_pname);
        sname = ks[random(sizeof(ks))];
        for (;;)
        {
                pname = kp[random(sizeof(kp))];
                if (pname != cn_sname[sname]) break;
        }
        id1 = cn_sname[sname];

        id2 = pname;
        pname = cn_pname[pname];
        pname = pname[(random(sizeof(pname)) & 0xFFFE)..<1];
        pname = pname[0..1];
        if (random(3) == 0)
        {
                for (;;)
                {
                        pname2 = kp[random(sizeof(kp))];
                        if (pname2 != cn_sname[sname] &&
                            pname2 != pname) break;
                }
                id2 += pname2;
                pname2 = cn_pname[pname2];
                pname2 = pname2[(random(sizeof(pname2)) & 0xFFFE)..<1];
                pname2 = pname2[0..1];
        } else
                pname2 = "";

        if (ob) ob->set_name(sname + pname + pname2,
                             ({ id1 + " " + id2, id1, id2 }));
}

mapping get_cn_name()
{
        string sname, pname, pname2, id1, id2;
        string *ks, *kp;

        ks = keys(cn_sname);
        kp = keys(cn_pname);
        sname = ks[random(sizeof(ks))];
        id1 = cn_sname[sname];
        for (;;)
        {
                pname = kp[random(sizeof(kp))];
                if (pname != id1 &&
                    ! find_living(id1 + " " + pname))
                        break;
        }

        id2 = pname;
        pname = cn_pname[pname];
        pname = pname[(random(sizeof(pname)) & 0xFFFE)..<1];
        pname = pname[0..1];
        if (random(3) == 0)
        {
                for (;;)
                {
                        pname2 = kp[random(sizeof(kp))];
                        if (pname2 != id1 && pname2 != pname &&
                            ! find_living(id1 + " " + pname + pname2)) break;
                }
                id2 += pname2;
                pname2 = cn_pname[pname2];
                pname2 = pname2[(random(sizeof(pname2)) & 0xFFFE)..<1];
                pname2 = pname2[0..1];
        } else
                pname2 = "";

        return ([ "name" : sname + pname + pname2,
                  "id"   : ({ id1 + " " + id2, id1, id2, }), ]);
}