// This program is a part of NT MudLIB
// group_questd.c

inherit F_DBASE;

// #pragma optimize
// #pragma save_binary

#include <ansi.h>
#include <command.h>
#include <npc/name.h>
#include <npc/chinese.c>
#include <npc/japanese.c>
#include <npc/european.c>
#include <npc/masia.c>
#include <npc/indian.c>

#define IDLE 3600
#define MAX_MOVED       5

nosave string *quest_name = ({
        "family",
        "waidi",
        "party",
});


nosave object running_quest;
nosave int step;
int all_enemy = 0;
int all_drop = 0;
object *all_killer = ({});

mapping levels = ([
//      combat_exp   skill_level
        100000      : 100,               // level 1
        170000      : 120,               // level 2
        340000      : 150,               // level 3
        600000      : 180,               // level 4
        800000      : 200,               // level 5
        1100000     : 220,               // level 6
        1600000     : 250,               // level 7
        2000000     : 270,               // level 8
        2500000     : 290,               // level 9
        3000000     : 310,               // level 10
        3600000     : 330,               // level 11
        4300000     : 350,               // level 12
        7000000     : 400,               // level 13
        9000000     : 450,               // level 14
        12500000    : 500,               // level 15
        17000000    : 550,               // level 16
        22000000    : 600,               // level 17
]);

mapping family = ([
        "少林派"   : ({ "/d/shaolin/zoulang1","/d/shaolin/hsyuan1",
                       "/d/shaolin/luohan1","/d/shaolin/luohan5",
                       "/d/shaolin/guangchang4","/d/shaolin/zoulang8",
                       "/d/shaolin/wuchang2","/d/shaolin/banruo2",
                       "/d/shaolin/bagua2","/d/shaolin/zhulin4", }),
        "武当派"   : ({ "/d/wudang/wdroad1","/d/wudang/gyroad1",
                       "/d/wudang/jindian","/d/wudang/shanlu4",
                       "/d/wudang/wuyaling","/d/wudang/zixiaogate",
                       "/d/wudang/taizipo", }),
        "丐帮"     : ({ "/d/city/ml1", "/d/city/ml2",
                       "/d/city/ml3", "/d/gaibang/pomiao",
                       "/d/gaibang/shoushe", "/d/gaibang/inhole",
                       "/d/city/ml4", "/d/gaibang/slandao1",
                       "/d/gaibang/slandao2", }),
        "全真教"   : ({ "/d/quanzhen/shanlu4","/d/quanzhen/shijie7",
                       "/d/quanzhen/houshan","/d/quanzhen/datang3", }),
        "华山派"   : ({ "/d/huashan/buwei1","/d/huashan/qunxianguan",
                       "/d/huashan/songlin1", }),
        "灵鹫宫"   : ({ "/d/lingjiu/changl1","/d/lingjiu/liangong",
                       "/d/lingjiu/huayuan","/d/lingjiu/changl6",}),
        "峨嵋派"   : ({ "/d/emei/jinding","/d/emei/woyunan",
                       "/d/emei/hcazhengdian","/d/emei/xiaolu1", }),
        "桃花岛"   : ({ "/d/taohua/taolin","/d/taohua/zhulin3", }),
        "明教"     : ({ "/d/mingjiao/shanmen","/d/mingjiao/shanlu2",
                       "/d/mingjiao/lhqpaifang","/d/mingjiao/lhqhoumen", }),
        "魔教"     : ({ "/d/yuanyue/shibanlu4","/d/yuanyue/senling1", }),
        "神龙教"   : ({ "/d/shenlong/fengding","/d/shenlong/wuchang", }),
        "古墓派"   : ({ "/d/gumu/zhengting","/d/gumu/qianting", }),
        "星宿派"   : ({ "/d/xingxiu/xxh1","/d/xingxiu/xxh2", }),
        "逍遥派"   : ({ "/d/xiaoyao/qingcaop","/d/xiaoyao/xiaodao4", }),
/*
        "血刀门"   : ({ "/d/xuedao/shandong2", "/d/xuedao/sroad9", }),
        "雪山寺"   : ({ "/d/xueshan/hubian1","/d/xueshan/chang",}),
*/
        "密宗"     : ({ "/d/xuedao/shandong2", "/d/xuedao/sroad9",
                        "/d/xueshan/hubian1","/d/xueshan/chang",}),
        "五毒教"   : ({ "/d/wudu/dating", "/d/wudu/wdsl7", }),
        "日月神教" : ({ "/d/heimuya/linjxd1","/d/heimuya/guang",
                       "/d/heimuya/linjxd2","/d/heimuya/shidao1",
                       "/d/heimuya/shidao2","/d/heimuya/xingxingtan",
                       "/d/heimuya/changtan", }),
        // add by wuji

        "铁掌帮" : ({ "/d/tiezhang/wztang","/d/tiezhang/hxfang",
                       "/d/tiezhang/pingtai","/d/tiezhang/xxs",
                       "/d/tiezhang/sslu-1","/d/tiezhang/dong3",  }),
        "凌霄城" : ({ "/d/lingxiao/cheng","/d/lingxiao/didi",
                       "/d/lingxiao/stone","/d/lingxiao/wave2",
                       "/d/lingxiao/fenghuo","/d/lingxiao/houyuan1",  }),
        "昆仑派" : ({ "/d/kunlun/shanbi","/d/kunlun/nanwoshi",
                       "/d/kunlun/lianwu","/d/kunlun/xianjing",
                       "/d/kunlun/xuedi","/d/kunlun/kunlun3",  }),
        "青城派" : ({ "/d/qingcheng/maguchi","/d/qingcheng/qiandian",
                       "/d/qingcheng/zoulang3","/d/qingcheng/woshi",
                       "/d/qingcheng/sandaoshi","/d/qingcheng/tianran",  }),
        "嵩山派" : ({ "/d/songshan/duzuntan","/d/songshan/eastting",
                       "/d/songshan/yunutai","/d/songshan/shuzhai",
                       "/d/songshan/taishique","/d/songshan/shandao2",  }),
        "泰山派" : ({ "/d/taishan/duzunju","/d/taishan/fengyue",
                       "/d/taishan/wudafu","/d/taishan/yitian",
                       "/d/taishan/muliyuan","/d/taishan/yaocan",  }),
        "恒山派" : ({ "/d/hengshan/beiyuemiao","/d/hengshan/baiyuan",
                       "/d/hengshan/jijiaooshi","/d/hengshan/hufengkou",
                       "/d/hengshan/shaodao2","/d/hengshan/zhaitang",  }),
        "衡山派" : ({ "/d/henshan/kefang","/d/henshan/inhole3",
                       "/d/henshan/houdian","/d/henshan/furong",
                       "/d/henshan/ontree2","/d/henshan/nantian",  }),

        "红花会" : ({ "/d/huijiang/damen","/d/huijiang/zongduo",
                       "/d/huijiang/xiagu","/d/huijiang/xiepo",
                       "/d/huijiang/goldroom","/d/huijiang/wuchang",  }),
        // end add
        "慕容世家" : ({ "/d/yanziwu/shuwu","/d/yanziwu/yimen", }),
        "关外胡家" : ({ "/d/guanwai/xiaowu","/d/guanwai/xiaoyuan",}),
        "段氏皇族" : ({ "/d/dali/neitang","/d/dali/chahua7",
                       "/d/dali/chahua3","/d/dali/wfdating", }),
        "欧阳世家" : ({ "/d/baituo/dating","/d/baituo/huayuan",
                       "/d/baituo/houyuan", }),
        "唐门世家" : ({ "/d/tangmen/tmdamen","/d/tangmen/gudao2",
                       "/d/tangmen/lianyunge","/d/tangmen/qianyuan", }),
]);

nosave mapping place = ([
        "北京东城": ({
                        "/d/beijing/cagc_e","/d/beijing/caroad_e1",
                        "/d/beijing/caroad_e2","/d/beijing/zahuo",
                        "/d/beijing/yancao","/d/beijing/xingchang",
                        "/d/beijing/wang_4","/d/beijing/chaoyang_dao1",
                        "/d/beijing/chaoyang_dao2","/d/beijing/chaoyangmen",
                        "/d/beijing/wang_6","/d/beijing/wang_8",
                        "/d/beijing/xiyuan","/d/beijing/xiyuanup",
                        "/d/beijing/wang_10","/d/beijing/wang_9",
                        "/d/beijing/wang_1","/d/beijing/wang_3",
                        "/d/beijing/wang_5","/d/beijing/wang_7",
                        "/d/beijing/wang_8","/d/beijing/quanjude",
                        "/d/beijing/quanjudeup","/d/beijing/dong_1",
                        "/d/beijing/dong_3","/d/beijing/dongchang_men",
                        "/d/beijing/dongchang","/d/beijing/xiaochang",
                        "/d/beijing/weifu_men","/d/beijing/weifu_zoulang1",
                        "/d/beijing/weifu_dayuan","/d/beijing/weifu_zoulang2",
                        "/d/beijing/weifu_dating","/d/beijing/weifu_shufang",
                        "/d/beijing/dong_2","/d/beijing/guozijian",
                        "/d/beijing/wang_2",
                     }),
        "北京西城" : ({
                        "/d/beijing/niaoshi","/d/beijing/xi_1",
                        "/d/beijing/caroad_w1","/d/beijing/yangliu1",
                        "/d/beijing/yangliu2","/d/beijing/yangliu3",
                        "/d/beijing/qingmu_men","/d/beijing/qingmu_dayuan",
                        "/d/beijing/qingmu_fang3","/d/beijing/qingmu_fang1",
                        "/d/beijing/caroad_w1","/d/beijing/caroad_w2",
                        "/d/beijing/cagc_w","/d/beijing/tiananmen",
                        "/d/beijing/cagc_s","/d/beijing/tianqiao",
                        "/d/beijing/yong_1","/d/beijing/duchang",
                        "/d/beijing/huiying","/d/beijing/huiyingup",
                        "/d/beijing/yong_2","/d/beijing/tiepu",
                        "/d/beijing/yong_3","/d/beijing/fu_2",
                        "/d/beijing/fukedian","/d/beijing/kediandayuan",
                        "/d/beijing/hai_men","/d/beijing/hai_dayuan",
                        "/d/beijing/hai_fang","/d/beijing/hai_huating",
                        "/d/beijing/hai_dating","/d/beijing/hai_houyuan",
                        "/d/beijing/mianguan","/d/beijing/fu_1",
                        "/d/beijing/tiantan_n","/d/beijing/tiantan",
                        "/d/beijing/yongdingdao","/d/beijing/yongdingmen",
                        "/d/beijing/qiao","/d/beijing/hgmen_s",
                        "/d/beijing/gaosheng","/d/beijing/xi_2",
                        "/d/beijing/huichuntang","/d/beijing/bei_2",
                        "/d/beijing/kangfu_men","/d/beijing/kangfu_dayuan",
                        "/d/beijing/kangfu_zoulang1","/d/beijing/kangfu_dating",
                        "/d/beijing/kangfu_zoulang2","/d/beijing/kangfu_xifang",
                        "/d/beijing/kangfu_dongfang","/d/beijing/kangfu_shufang",
                        "/d/beijing/bei_2","/d/beijing/bei_4",
                        "/d/beijing/di_1","/d/beijing/di_3",
                        "/d/beijing/di_4","/d/beijing/aofu_men",
                        "/d/beijing/aofu_zoulang1","/d/beijing/aofu_dayuan",
                        "/d/beijing/aofu_dating","/d/beijing/aofu_zoulang2",
                        "/d/beijing/aofu_houyuan","/d/beijing/aofu_zoulang3",
                        "/d/beijing/aofu_shufang","/d/beijing/aofu_naofang",
                        "/d/beijing/caishi","/d/beijing/ximenkou",
                        "/d/beijing/shi_1","/d/beijing/guandao_1",
                        "/d/beijing/guandao_2","/d/beijing/huangling",
                        "/d/beijing/shi_3","/d/beijing/di_xigc",
                        "/d/beijing/di_2","/d/beijing/dianmen",
                        "/d/beijing/di_dajie1","/d/beijing/di_5",
                        "/d/beijing/di_dajie2","/d/beijing/di_anmen",
                        "/d/beijing/qingmu_dating",
                     }),
        "扬州城"   : ({
                        "/d/city/zuixianlou2","/d/city/zuixianlou3",
                        "/d/city/zuixianlou","/d/city/beidajie2",
                        "/d/city/beimen","/d/city/beidajie1",
                        "/d/city/qianzhuang","/d/city/guangchang",
                        "/d/city/xidajie1","/d/city/yamen",
                        "/d/city/xidajie2","/d/city/wuguan",
                        "/d/city/ximen","/d/city/dongdajie1",
                        "/d/city/zahuopu","/d/city/dongdajie2",
                        "/d/city/yaopu","/d/city/datiepu",
                        "/d/city/dongmen",
                     }),
         "长安城"   : ({
                        "/d/changan/huanggong","/d/changan/bridge1",
                        "/d/changan/baihu2","/d/changan/beian-dadao",
                        "/d/changan/beian-daokou","/d/changan/bingying1",
                        "/d/changan/bingying2","/d/changan/bei-chengmen",
                        "/d/changan/qixiang3","/d/changan/qixiang2",
                        "/d/changan/tea-shop","/d/changan/fruit-shop",
                        "/d/changan/qixiang1","/d/changan/jiulou",
                        "/d/changan/jiulou2","/d/changan/yongtai-beikou",
                        "/d/changan/zhubaohang","/d/changan/yongtai-dadao1",
                        "/d/changan/yongtai-dadao2","/d/changan/yongtai-dadao3",
                        "/d/changan/huiwenge","/d/changan/xian-daokou",
                        "/d/changan/xi-chengmen","/d/changan/bingying3",
                        "/d/changan/yongtai-dadao4","/d/changan/miao",
                        "/d/changan/yongtai-dadao5","/d/changan/yongtai-nankou",
                        "/d/changan/baozipu","/d/changan/huarui1",
                        "/d/changan/nanan-daokou","/d/changan/huarui2",
                        "/d/changan/mianguan","/d/changan/huarui3",
                        "/d/changan/huadian","/d/changan/bingying5",
                        "/d/changan/bingying4","/d/changan/nan-chengmen",
                        "/d/changan/huarui4","/d/changan/xiaojinghu",
                        "/d/changan/huarui4","/d/changan/huarui5",
                        "/d/changan/zahuopu","/d/changan/huarui5",
                        "/d/changan/huarui6","/d/changan/tuchangguan",
                        "/d/changan/liande-nankou","/d/changan/xiaojiuguan",
                        "/d/changan/liande-dadao5","/d/changan/xiaojia-qianyuan",
                        "/d/changan/liande-dadao4","/d/changan/dongan-daokou",
                        "/d/changan/dong-chengmen","/d/changan/bingying6",
                        "/d/changan/liande-dadao3","/d/changan/liande-dadao2",
                        "/d/changan/liande-dadao1","/d/changan/liande-beikou",
                        "/d/changan/xiyuan","/d/changan/qixiang6",
                        "/d/changan/yaopu","/d/changan/weapon-shop",
                        "/d/changan/qixiang5","/d/changan/shoushi-dian",
                        "/d/changan/biaoju-damen","/d/changan/qixiang4",
                        "/d/changan/bank","/d/changan/qunyulou",
                        "/d/changan/baihu1","/d/changan/fufeng1",
                        "/d/changan/fufeng2","/d/changan/fufeng3",
                        "/d/changan/fufeng4","/d/changan/xian-dadao",
                        "/d/changan/fufeng5","/d/changan/qinglong1",
                        "/d/changan/baoxiangsi","/d/changan/qinglong2",
                        "/d/changan/bridge2","/d/changan/qinglong2",
                        "/d/changan/nanan-dadao","/d/changan/qinglong3",
                        "/d/changan/yamen","/d/changan/fengxu5",
                        "/d/changan/fengxu4","/d/changan/lingyange",
                        "/d/changan/fengxu3","/d/changan/fengxu2",
                        "/d/changan/dongan-dadao","/d/changan/fengxu1",
                        "/d/changan/baihu3","/d/changan/guozijian",
                     }),
        "成都城"   : ({
                        "/d/chengdu/guangchang","/d/chengdu/tidugate",
                        "/d/chengdu/shuduroad2","/d/chengdu/shuduroad1",
                        "/d/chengdu/eastroad2","/d/chengdu/eastroad1",
                        "/d/chengdu/northroad3","/d/chengdu/northroad2",
                        "/d/chengdu/northgate","/d/chengdu/northroad1",
                        "/d/chengdu/bingqidian","/d/chengdu/westroad3",
                        "/d/chengdu/yaodian","/d/chengdu/westroad2",
                        "/d/chengdu/westgate","/d/chengdu/westroad1",
                        "/d/chengdu/qingyanggong","/d/chengdu/southroad3",
                        "/d/chengdu/wuhoucigate","/d/chengdu/liubeidian",
                        "/d/chengdu/wuhouci","/d/chengdu/southroad2",
                        "/d/chengdu/southgate","/d/chengdu/tiduroad",
                        "/d/chengdu/southroad1","/d/chengdu/eastroad3",
                        "/d/chengdu/wangjianglou","/d/chengdu/eastroad2",
                        "/d/chengdu/eastroad1","/d/chengdu/jiudian",
                        "/d/chengdu/wuguan",
                     }),
        "苏州城"   : ({
                        "/d/suzhou/beimen","/d/suzhou/beidajie2",
                        "/d/suzhou/zijinan","/d/suzhou/jiudian",
                        "/d/suzhou/beidajie1","/d/suzhou/xiyuan",
                        "/d/suzhou/canlangting","/d/suzhou/dongdajie1",
                        "/d/suzhou/hutong1","/d/suzhou/leitai",
                        "/d/suzhou/hutong2","/d/suzhou/hutong3",
                        "/d/suzhou/dongdajie2","/d/suzhou/dongmen",
                        "/d/suzhou/yaopu","/d/suzhou/datiepu",
                        "/d/suzhou/baodaiqiao","/d/suzhou/nandajie1",
                        "/d/suzhou/jubaozhai","/d/suzhou/shizilin",
                        "/d/suzhou/yanyutang","/d/suzhou/zhenquting",
                        "/d/suzhou/wenmeige","/d/suzhou/lixuetang",
                        "/d/suzhou/zhipoxuan","/d/suzhou/shuyuan",
                        "/d/suzhou/chaguan","/d/suzhou/nandajie2",
                        "/d/suzhou/liuyuan","/d/suzhou/hehuating",
                        "/d/suzhou/gumujiaohe","/d/suzhou/chitang",
                        "/d/suzhou/nanmen","/d/suzhou/tingyu",
                        "/d/suzhou/xidajie1","/d/suzhou/bingying",
                        "/d/suzhou/szyunhe","/d/suzhou/xidajie2",
                        "/d/suzhou/xuanmiao","/d/suzhou/shuchang",
                        "/d/suzhou/ximen",
                     }),
        "杭州城"   : ({
                        "/d/hangzhou/suti2", "/d/hangzhou/jujingyuan",
                        "/d/hangzhou/liuzhuang", "/d/hangzhou/road19",
                        "/d/hangzhou/huangniling", "/d/hangzhou/qinglindong",
                        "/d/hangzhou/road5","/d/hangzhou/liuhe2",
                        "/d/hangzhou/dadao1","/d/hangzhou/xilingqiao",
                        "/d/hangzhou/road9","/d/hangzhou/baoshishan",
                        "/d/hangzhou/yuelang","/d/hangzhou/liuzhuang1",
                        "/d/hangzhou/huagang","/d/hangzhou/hupaoquan",
                        "/d/hangzhou/yuhuangsd","/d/hangzhou/yuhuangshan",
                        "/d/hangzhou/shanlu6","/d/hangzhou/shanlu7",
                        "/d/hangzhou/yuhuangsj","/d/hangzhou/road18",
                        "/d/hangzhou/road20","/d/hangzhou/suti7",
                        "/d/hangzhou/suti7","/d/hangzhou/suti6",
                        "/d/hangzhou/suti5","/d/hangzhou/suti4",
                        "/d/hangzhou/suti3","/d/hangzhou/suti2",
                        "/d/hangzhou/road7","/d/hangzhou/road8",
                        "/d/hangzhou/road9","/d/hangzhou/road10",
                        "/d/hangzhou/road11","/d/hangzhou/road12",
                        "/d/hangzhou/road13","/d/hangzhou/road14",
                        "/d/hangzhou/road15","/d/hangzhou/road16",
                        "/d/hangzhou/xizhaoshan","/d/hangzhou/road17",
                        "/d/hangzhou/road18","/d/hangzhou/qingbomen",
                        "/d/hangzhou/jujingyuan","/d/hangzhou/liulangqiao",
                        "/d/hangzhou/qiantang","/d/hangzhou/liuheta",
                        "/d/hangzhou/yuquan","/d/hangzhou/dadao1",
                        "/d/hangzhou/dadao2","/d/hangzhou/dalu1",
                        "/d/hangzhou/liuzhuang2","/d/hangzhou/liuzhuang",
                        "/d/hangzhou/road1", "/d/hangzhou/road2",
                        "/d/hangzhou/road4", "/d/hangzhou/road3",
                        "/d/hangzhou/hongchunqiao","/d/hangzhou/jiulou",
                        "/d/hangzhou/duanqiao","/d/hangzhou/baiti",
                        "/d/hangzhou/pinghuqiuyue","/d/hangzhou/fangheting",
                        "/d/hangzhou/gushan","/d/hangzhou/gushanpingtai",
                        "/d/meizhuang/shijie","/d/meizhuang/xiaolu",
                        "/d/meizhuang/gate","/d/hangzhou/shanlu8",
                        "/d/hangzhou/chufang","/d/hangzhou/tiejiangpu",
                        "/d/hangzhou/yaodian","/d/hangzhou/jingcisi",
                        "/d/hangzhou/jingci","/d/hangzhou/shanlu1",
                        "/d/hangzhou/shanlu2","/d/hangzhou/shanlu3",
                        "/d/hangzhou/fajingsi","/d/hangzhou/fajinsi",
                        "/d/hangzhou/faxisi","/d/hangzhou/shanlu4",
                        "/d/hangzhou/shanlu5","/d/hangzhou/shanlu6",
                        "/d/hangzhou/shanlu7","/d/hangzhou/tulu1",
                        "/d/hangzhou/yanxiadong","/d/hangzhou/maojiabu",
                        "/d/hangzhou/maojiabu","/d/hangzhou/huangniling",
                        "/d/hangzhou/shuiledong","/d/hangzhou/manjuelong",
                     }),
        "襄阳城"   : ({
                        "/d/xiangyang/westjie2", "/d/xiangyang/southjie2",
                        "/d/xiangyang/xiaorong1", "/d/xiangyang/zhonglie",
                        "/d/xiangyang/guangchang", "/d/xiangyang/dingzi",
                        "/d/xiangyang/westgate2","/d/xiangyang/northgate1",
                        "/d/xiangyang/eastgate1","/d/xiangyang/southgate2",
                        "/d/xiangyang/walls2","/d/xiangyang/walle3",
                        "/d/xiangyang/walln4","/d/xiangyang/juyilang",
                        "/d/xiangyang/northgate2","/d/xiangyang/northjie",
                        "/d/xiangyang/bingying1","/d/xiangyang/chaguan",
                        "/d/xiangyang/northroad2","/d/xiangyang/xiaorong2",
                        "/d/xiangyang/xiaorong1","/d/xiangyang/jiekou2",
                        "/d/xiangyang/eastroad2","/d/xiangyang/eastroad1",
                        "/d/xiangyang/biaoju","/d/xiangyang/eastjie2",
                        "/d/xiangyang/eastjie3","/d/xiangyang/bingying2",
                        "/d/xiangyang/eastgate2","/d/xiangyang/walle1",
                        "/d/xiangyang/walle5","/d/xiangyang/walle7",
                        "/d/xiangyang/walle2","/d/xiangyang/walle4",
                        "/d/xiangyang/walle6","/d/xiangyang/walle8",
                        "/d/xiangyang/mujiang","/d/xiangyang/eastjie2",
                        "/d/xiangyang/eastjie3","/d/xiangyang/jiedao",
                        "/d/xiangyang/minju2","/d/xiangyang/eastjie1",
                        "/d/xiangyang/jiangjungate","/d/xiangyang/yaopu",
                        "/d/xiangyang/anfugate","/d/xiangyang/anfupailou",
                        "/d/xiangyang/southjie1","/d/xiangyang/southjie2",
                        "/d/xiangyang/southjie3","/d/xiangyang/xuetang",
                        "/d/xiangyang/qianzhuang","/d/xiangyang/southgate1",
                        "/d/xiangyang/nixianglou","/d/xiangyang/duchang",
                        "/d/xiangyang/tiejiangpu","/d/xiangyang/bingying3",
                        "/d/xiangyang/walls1","/d/xiangyang/walls3",
                        "/d/xiangyang/walls5","/d/xiangyang/walls7",
                        "/d/xiangyang/walls4","/d/xiangyang/walls6",
                        "/d/xiangyang/walls8","/d/xiangyang/westjie1",
                        "/d/xiangyang/westjie2","/d/xiangyang/westjie3",
                        "/d/xiangyang/juyiyuan","/d/xiangyang/juyilianwu2",
                        "/d/xiangyang/juyilianwu1","/d/xiangyang/juyilang",
                        "/d/xiangyang/juyihuayuan","/d/xiangyang/juyimale",
                        "/d/xiangyang/juyifemale","/d/xiangyang/juyichufang",
                        "/d/xiangyang/juyiwupin","/d/xiangyang/dajiaochang",
                        "/d/xiangyang/bingying4","/d/xiangyang/westgate1",
                        "/d/xiangyang/wallw1","/d/xiangyang/wallw2",
                        "/d/xiangyang/wallw3","/d/xiangyang/wallw4",
                        "/d/xiangyang/wallw5","/d/xiangyang/wallw6",
                        "/d/xiangyang/wallw7","/d/xiangyang/wallw8",
                        "/d/xiangyang/westroad1","/d/xiangyang/westroad2",
                        "/d/xiangyang/shudian","/d/xiangyang/hutong1",
                        "/d/xiangyang/hutong2","/d/xiangyang/xinluofang",
                        "/d/xiangyang/jiekou1","/d/xiangyang/northgate2",
                        "/d/xiangyang/walln1","/d/xiangyang/walln2",
                        "/d/xiangyang/walln3","/d/xiangyang/walln5",
                        "/d/xiangyang/walln6","/d/xiangyang/walln7",
                        "/d/xiangyang/walln8",
                     }),

        "大理一带" : ({
                        "/d/dali/northgate", "/d/dali/southgate",
                        "/d/dali/shanlu2", "/d/dali/buxiongbu",
                        "/d/dali/jinzhihe", "/d/dali/xiaodao1",
                        "/d/dali/tianweijing", "/d/dali/wuding",
                        "/d/dali/luwang", "/d/dali/gudao",
                        "/d/dali/biluoxueshan", "/d/dali/zhenxiong",
                        "/d/dali/yixibu", "/d/dali/cangshanzhong",
                        "/d/dali/wumeng", "/d/dali/hongsheng",
                        "/d/dali/tusifu","/d/dali/tusimentang",
                        "/d/dali/tusiyishi","/d/dali/dahejiewest",
                        "/d/dali/dahejieeast","/d/dali/baiyiziguan",
                        "/d/dali/baiyiminju","/d/dali/center",
                        "/d/dali/taihejiekou","/d/dali/sheguta",
                        "/d/dali/qingchi","/d/dali/taiheeast",
                        "/d/dali/stoneshop","/d/dali/garments",
                        "/d/dali/yaoshop","/d/dali/paifang",
                        "/d/dali/yujie","/d/dali/gongmen",
                        "/d/dali/qiandian","/d/dali/yuhuayuan",
                        "/d/dali/hualang","/d/dali/yushanfang",
                        "/d/dali/piandian","/d/dali/chahuashan1",
                        "/d/dali/chahuashan2","/d/dali/chahuashan3",
                        "/d/dali/chahuashan4","/d/dali/chahuashan5",
                        "/d/dali/chahuashan6","/d/dali/dadieshui",
                        "/d/dali/qingxi","/d/dali/xiaodao1",
                        "/d/dali/hudiequan","/d/dali/yuxuguanqian",
                     }),
]);

string *nations = ({ "日本", "荷兰", "天竺", "日本", "日本",
                     "日本", "英吉利", "法兰西", "西班牙", "葡萄牙",
                     "比利时"});

string *foreigner = ({ "佣兵团", "探险队", "侵略军", "亡命团伙", "流窜犯" });

string *chinese = ({ "黑风寨", "斧头帮", "山西土匪", "山东响马", "湘西土匪",
                     "乌龙岗强盗", "太行山土匪", "落日峰毛贼", "荒漠大盗" });

void add_killer(object killer);
void be_killed(int num);
int query_enemy();
object *query_killer();
object create_npc(string nation, int lvl);
void init_npc_skill(object ob, int lvl);
varargs void place_npc(object ob,string arg,string the_type,int lvl,string pp);
void random_move(object ob);
void set_enemy(int num);
int filter_listener(object ob);

void add_killer(object killer)
{
        if (!objectp(killer) || !userp(killer))
                return;

        if (member_array(killer,all_killer) == -1)
                all_killer += ({ killer });

        return;
}

int add_drop(int num)
{
        all_drop += num;
        return all_drop;
}

void be_killed(int num)
{
        object *listeners;

        all_enemy -= num;
        listeners = filter_array(users(), (: filter_listener :));
        if (all_enemy <= 0)
                message("group_quest",HIR "【情报】" NOR + HIY + "太棒了！所有的敌人全部都给消灭了！\n" + NOR,listeners);
        else if (all_enemy < 6)
                message("group_quest",HIR "【情报】" NOR + HIY + "加油啊！根据最新情报，还剩下" + chinese_number(all_enemy) + "个敌人！\n" + NOR,listeners);
        return;
}


int query_enemy()
{
        return all_enemy;
}

int query_drop()
{
        return all_drop;
}

object *query_killer()
{
        return all_killer;
}

void ready_to_start()
{
        remove_call_out("start_quest");
        remove_call_out("process_quest");
        call_out("start_quest", IDLE);
}

void go_on_process(object ob)
{
        remove_call_out("start_quest");
        remove_call_out("process_quest");
        call_out("process_quest", 1, ob);
}

void create()
{
        seteuid(ROOT_UID);
        set("channel_id", "任务精灵");
        CHANNEL_D->do_channel( this_object(), "sys", "群组任务系统已经启动。");
        ready_to_start();
}

int clean_up()
{
        return 1;
}

object query_running_quest()
{
        return running_quest;
}

object create_npc(string nation, int lvl)
{
        object ob;

        switch (nation)
        {
        case "中国":
                ob = new(CLASS_D("generate") + "/quest_chinese");
                NPC_D->generate_cn_name(ob);
                break;
        case "日本":
                ob = new(CLASS_D("generate") + "/quest_japanese");
                NPC_D->generate_jp_name(ob);
                break;
        case "英吉利":
        case "法兰西":
        case "西班牙":
        case "葡萄牙":
        case "比利时":
        case "荷兰":
                ob = new(CLASS_D("generate") + "/quest_european");
                generate_e_name(ob);
                break;
        case "天竺":
                ob = new(CLASS_D("generate") + "/quest_indian");
                generate_in_name(ob);
                break;
        }
        if (lvl >= 7)
                set("auto_perform", 1, ob);
        set("nation", nation, ob);
        init_npc_skill(ob, lvl);

        return ob;
}

// set the the level of the npc's skill
void init_npc_skill(object ob, int lvl)
{
        int sk_lvl;
        string *ks;
        int i;
        int exp;
        mixed my;

        if (lvl < 1) lvl = 1;
        if (lvl > sizeof(levels)) lvl = sizeof(levels);

        exp = sort_array(keys(levels), 1)[lvl - 1];
        my = ob->query_entire_dbase();
        set("combat_exp", exp, ob);
        sk_lvl = levels[exp];
        my["jing"] = my["eff_jing"] = my["max_jing"] = sk_lvl * 10;
        my["qi"] = my["eff_qi"] = my["max_qi"] = sk_lvl * 20;
        my["jingli"] = my["max_jingli"] = sk_lvl * 10;
        my["neili"] = my["max_neili"] = sk_lvl * 20;
        addn_temp("apply/attack", sk_lvl/4, ob);
        addn_temp("apply/dodge", sk_lvl/8, ob);
        addn_temp("apply/parry", sk_lvl/8, ob);
        addn_temp("apply/damage", sk_lvl/2, ob);
        addn_temp("apply/armor", sk_lvl/2, ob);
        if (! ob->query_skills())
                return;
        ks = keys(ob->query_skills());
        for (i = 0; i < sizeof(ks); i++)
                ob->set_skill(ks[i], sk_lvl);
        set("jiali", ob->query_skill("force")/2, ob);
}

void start_quest()
{
        string *all_quest;
        string name;
        object ob;
        int *nowtime = TIME_D->query_realtime_array();

        ready_to_start();
        if( nowtime[1] < 9 ) return;
        CHANNEL_D->do_channel(this_object(), "sys", "群组任务系统开始选择任务。");

        all_quest = quest_name;

        while (sizeof(all_quest))
        {
                name = all_quest[random(sizeof(all_quest))];

                CHANNEL_D->do_channel(this_object(), "sys",
                                      "群组任务系统选择了任务(" + name + ")。");

                all_quest -= ({ name });
                name = GROUP_QUEST_DIR + name;
                if (ob = find_object(name))
                        destruct(ob);

                catch(ob = load_object(name));
                running_quest = ob;

                if (objectp(ob))
                {
                        step = 0;
                        all_killer = ({});
                        all_enemy = 0;
                        all_drop = 0;
                        go_on_process(ob);
                        break;
                }
        }
}

void process_quest(object ob)
{
        mixed line;
        object *listeners;
        string prompt;

        go_on_process(ob);

        if (! objectp(ob))
        {
                ready_to_start();
                return;
        }

        line = ob->query_quest_message(step);
        step++;

        prompt = ob->prompt();
        //if (! prompt) prompt = HIR "【群组任务】" NOR;
        if (! prompt) prompt = HIR "【群组】" NOR;
        if (functionp(line)) catch(line = evaluate(line));
        if (stringp(line))
        {
                listeners = filter_array(users(), (: filter_listener :));
                message( "group_quest",  prompt + WHT + line + "\n" NOR, listeners );
        }

        if (intp(line) && ! line)
        {
                ready_to_start();
                destruct(ob);
        }
}

varargs void place_npc(object ob,string arg,string the_type,int lvl,string pp)
{
        string *kp;
        string option;
        string p, startroom;
        object pos;

        switch (arg)
        {
                case "外敌":
                        set("my_type", arg, ob);
                        startroom = place[the_type][random(sizeof(place[the_type]))];
                        if (! objectp(pos = get_object(startroom)))
                                log_file("log", sprintf("error to place npc to %s:%s\n",
                                                        the_type, startroom));
                        set("place", the_type, ob);
                        break;
                case "门派":
                        set("my_type", arg, ob);
                        set("门派", the_type, ob);
                        startroom = family[the_type][random(sizeof(family[the_type]))];
                        if (! objectp(pos = get_object(startroom)))
                                log_file("log", sprintf("error to place npc to %s:%s\n",
                                                        the_type, startroom));
                        set("place", the_type, ob);
                        break;
                case "帮派":
                        set("my_type", arg, ob);
                        set("帮派", the_type, ob);
                        startroom = place[pp][random(sizeof(place[pp]))];
                        if (! objectp(pos = get_object(startroom)))
                                log_file("log", sprintf("error to place npc to %s:%s\n",
                                                        the_type, startroom));
                        set("place", pp, ob);
                        break;

        }

        switch (lvl)
        {
                case 1:
                case 2:
                case 3:
                        set("nickname", "小喽罗", ob);
                        set("bonus", 600, ob);
                        break;
                case 4:
                case 5:
                case 6:
                        set("nickname", "普通成员", ob);
                        set("bonus", 800, ob);
                        break;
                case 7:
                case 8:
                case 9:
                        set("nickname", "小头目", ob);
                        set("bonus", 1000, ob);
                        break;
                case 10:
                case 11:
                case 12:
                        set("nickname", "大头目", ob);
                        set("bonus", 1500, ob);
                        break;
                case 13:
                case 14:
                        set("nickname", "首领", ob);
                        set("bonus", 2000, ob);
                        break;
                case 15:
                case 16:
                        set("nickname", "大首领", ob);
                        set("bonus", 3000, ob);
                        break;
                default:
                        set("nickname", "总首领", ob);
                        set("bonus", 5000, ob);
                        break;
        }

        ob->move(pos);
        set("startroom", startroom, ob);
        set_temp("moved", ({}), ob);
        message_vision("$N走了过来。\n", ob);
}

// random move
void random_move(object ob)
{
        mapping exits;
        string *moved;
        string dir;
        string *dirs;
        int i;

        moved=query_temp("moved", ob);
        if (! moved) moved = ({ });
        if (sizeof(moved) >= MAX_MOVED)
        {
                // out of range, move back
                dir = GO_CMD->query_reverse(moved[sizeof(moved) - 1]);
        } else
        {
                exits=query("exits", environment(ob));
                if (! mapp(exits) || sizeof(exits) < 1)
                        return;

                dirs = keys(exits);
                for (i = 0; i < 12; i++)
                {
                        if (! sizeof(dirs))
                                return;
                        dir = dirs[random(sizeof(dirs))];

                        if( !get_object(exits[dir]) )
                        {
                                dirs -= ({ dir });
                                continue;
                        }

                        if (stringp(GO_CMD->query_reverse(dir)) &&
                            !query("no_fight", get_object(exits[dir])) )
                                break;
                        dirs -= ({ dir });
                }
        }

        if (sizeof(moved) &&
            GO_CMD->query_reverse(dir) == moved[sizeof(moved) - 1])
        {
                // move back
                moved = moved[0..<2];
        } else
                moved += ({ dir });
        set_temp("moved", moved, ob);

        GO_CMD->main(ob, dir);
}

string query_place()
{
        string *kp;
        string p;

        kp = keys(place);
        p = kp[random(sizeof(kp))];
        return p;
}

string query_nation()
{
        return nations[random(sizeof(nations))];
}

string get_title(string the_nation,int num)
{
        string title;

        title = HIW + the_nation + NOR + " " + HIY +
                foreigner[random(sizeof(foreigner))] +NOR;

        return title;
}

string get_enemy()
{
        return chinese[random(sizeof(chinese))];
}

void set_enemy(int num)
{
        all_enemy = num;
}
//本函数用于查找地点列表的错误
void check_all_place()
{
        int i,j;
        string *all_city, *the_place;
        object env;

        all_city = keys(place);
        for (i = 0;i < sizeof(all_city);i++)
        {
                the_place = place[all_city[i]];
                for (j = 0;j<sizeof(the_place);j++)
                {
                        write(the_place[j] + "\n");
                        if (!objectp(env = get_object(the_place[j])))
                                log_file("static/party_quest",sprintf("门派任务错误记录：%s\n",the_place[j]));
                }
        }
}

string *get_family()
{
        return keys(family);
}

int filter_listener(object ob)
{
        if( !query("channels", ob))return 0;
        //if( member_array("task",query("channels", ob)) == -1)return 0;
        if( query("env/no_task", ob) )return 0;
        return 1;
}
