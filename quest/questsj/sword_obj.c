// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping sword_obj = ([
        "/d/yanziwu/npc/obj/changjian":30,            //阿朱、阿碧
        "/d/xiangyang/npc/obj/mujian":5,              //木匠购买
        "/d/xiakedao/obj/baihongjian":5,              //侠客岛石洞
        "/d/wudang/quest/obj/ghost_sword":10,         //武当桃树枝
        "/d/wanjiegu/npc/obj/tie-gan":35,             //段延庆
        "/d/village/obj/zhujian":5,                   //灵鹫武器库、侠客岛武器库、苏州小贩、武当练功房
        "/d/village/npc/obj/youlong":35,              //冯铁匠
        "/d/tulong/tulong/obj/ling1":32,              //流云使
        "/d/tulong/obj/yitianjian":35,                //赵敏
        "/d/tulong/obj/duan1":0,                      //断了的依天剑
        "/d/taohua/obj/yuxiao":35,                    //黄药师
        "/d/taohua/obj/taojian":18,                   //桃花岛兵器库
        "/d/shaolin/obj/zhujian":18,                  //少林兵器库
        "/d/shaolin/obj/changjian":10,                //少林一些和尚、道尘禅师索取
        "/d/quanzhou/pig/obj/cleansword":1,           //暂时无处获取
        "/d/quanzhou/obj/xiuhua":5,                   //胡掌柜购买
        "/d/quanzhou/npc/obj/xiuhua":1,               //暂时无处获取
        "/d/quanzhen/npc/obj/gangjian":22,            //全真禅房、武功镇武将（两个）
        "/d/mingjiao/obj/changjian":1,                //暂时无处获取
        "/d/meizhuang/obj/sea-wood":32,               //琴音小院
        "/d/meizhuang/obj/qin":1,                     //暂时无处获取
        "/d/jinshe/obj/jinshe-jian":32,               //金蛇洞
        "/d/huashan/obj/longquan":30,                 //华山居室
        "/d/huashan/npc/obj/green_water_sword":35,    //岳灵珊
        "/d/heimuya/obj/yuxiao":35,                   //东方不败
        "/d/heimuya/npc/obj/zhen":1,                  //暂时无处获取
        "/d/heimuya/npc/obj/changjian":30,            //桑三娘、任盈盈
        "/d/hangzhou/honghua/obj/shortsword":35,      //霍青桐
        "/d/gumu/npc/obj/shunvjian":35,               //小龙女
        "/d/gumu/npc/obj/junzijian":35,               //小龙女
        "/d/fuzhou/obj/xiuhua":5,                     //很多
        "/d/fuzhou/npc/obj/xiuhua":1,                 //暂时无处获取
        "/d/emei/obj/zhujian":25,                     //峨嵋储物间
        "/d/emei/obj/skysword":1,                     //暂时无处获取
        "/d/emei/obj/ruanjian":35,                    //静风师太
        "/d/city/obj/gangjian":18,                    //白衣卫士（六个）
        "/d/city/obj/duanjian":12,                    //相当多
        "/d/city/obj/changjian":10,                   //相当多
        "/d/city/obj/branch1":18,                     //蛇谷
        "/d/city/obj/branch":18,                      //蛇谷
        "/d/city/npc/obj/gangjian":10,                //相当多
        "/d/city/npc/obj/duanjian":1,                 //暂时无处获取
        "/d/city/npc/obj/changjian":15,               //程玉环、丁坚、史令威、梅庄护院
        "/d/changan/npc/obj/sword":12,                //群玉楼保镖、梁兴禄
        "/d/changan/npc/obj/changjian":10,            //慕容豪、武将
        "/d/beijing/npc/obj/sword5":20,               //东厂官兵
        "/d/beijing/npc/obj/sword4":15,               //西厂官兵、城门督察、御前侍卫、骁骑营侍卫、张康年、赵齐贤
        "/d/beijing/npc/obj/sword3":35,               //冯锡范
        "/d/beijing/npc/obj/sword2":20,               //剑僧
        "/d/beijing/npc/obj/sword1":30,               //归二娘
        "/d/beijing/npc/obj/bishou":35,               //鳌拜
        "/d/beijing/npc/obj/baojian":1,               //暂时无处获取
        "/clone/weapon/zhujian":5,                    //很多
        "/clone/weapon/xiyang-sword":10,              //日本外敌
        "/clone/weapon/green_sword":35,               //张召重
        "/clone/weapon/gangjian":5,                   //很多
        "/clone/weapon/duanjian":1,                   //暂时无处获取
        "/clone/weapon/changjian":5,                  //很多
        "/clone/book/shenghuo-ling":35,               //张无忌
        "/kungfu/class/dali/obj/tiedi":35,            //高升泰
]);

int check_value(string filename)
{
        if (undefinedp(sword_obj[filename])) return 0;
        return sword_obj[filename];
}
