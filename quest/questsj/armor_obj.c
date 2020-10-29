// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping armor_obj = ([
        "/d/yanziwu/npc/obj/goldring":30,     //阿朱、阿碧
        "/d/wanjiegu/npc/obj/jade-belt":1,    //暂时无处获取
        "/d/wanjiegu/npc/obj/belt":1,         //暂时无处获取
        "/d/tulong/yitian/npc/obj/gong":20,   //神箭八雄
        "/d/taohua/obj/ruanwei":30,           //黄蓉、郭芙
        "/d/shaolin/obj/zhitao":18,           //向武修文、道相禅师索取
        "/d/shaolin/obj/yaodai":1,            //暂时无处获取
        "/d/shaolin/obj/tieshou":26,          //打铁僧（一次三个）
        "/d/shaolin/obj/shoutao":18,          //向武修文、道相禅师索取
        "/d/shaolin/obj/huyao":18,            //向武修文、道相禅师索取
        "/d/shaolin/obj/huwan":18,            //向武修文、道相禅师索取
        "/d/quanzhen/npc/obj/tiejia":22,      //全真禅房、武功镇武将（两个）
        "/d/mingjiao/obj/zhitao":1,           //暂时无处获取
        "/d/mingjiao/obj/yaodai":1,           //暂时无处获取
        "/d/mingjiao/obj/tieshou":1,          //暂时无处获取
        "/d/mingjiao/obj/shoutao":1,          //暂时无处获取
        "/d/mingjiao/obj/huyao":1,            //暂时无处获取
        "/d/mingjiao/obj/huwan":1,            //暂时无处获取
        "/d/heimuya/npc/obj/jin":36,          //任盈盈
        "/d/emei/obj/yaodai":33,              //峨嵋储物间
        "/d/dali/npc/obj/tiejia":23,          //大理武将（一次五个）
        "/d/city/obj/zhitao":1,               //暂时无处获取
        "/d/city/obj/tieshou":1,              //暂时无处获取
        "/d/city/obj/tiejia":1,               //暂时无处获取
        "/d/city/obj/surcoat":5,              //很多
        "/d/city/obj/shoutao":1,              //暂时无处获取
        "/d/city/obj/shield":1,               //暂时无处获取
        "/d/city/obj/huyao":1,                //暂时无处获取
        "/d/city/obj/huwan":1,                //暂时无处获取
        "/d/city/obj/goldring":8,             //福州、泉州杂货铺陈阿婆购买
        "/d/city/npc/obj/zhitao":10,          //杨永福、高丽商人购买
        "/d/city/npc/obj/tieshou":5,          //杨永福、高丽商人购买
        "/d/city/npc/obj/tiejia":5,           //很多
        "/d/city/npc/obj/surcoat":5,          //杨永福、高丽商人购买
        "/d/city/npc/obj/shoutao":1,          //杨永福、高丽商人购买
        "/d/city/npc/obj/shield":8,           //杨永福、高丽商人购买
        "/d/city/npc/obj/huyao":6,            //杨永福、高丽商人购买
        "/d/city/npc/obj/huwan":6,            //杨永福、高丽商人购买
        "/d/city/npc/obj/goldring":33,        //程玉环
        "/d/city/npc/cloth/jade-belt":3,      //曾柔购买
        "/d/city/npc/cloth/belt":8,           //曾柔购买
        "/d/changan/npc/obj/zuanjie":18,      //陈老板购买
        "/d/changan/npc/obj/zhanjia":22,      //有不少
        "/d/changan/npc/obj/yinjie":7,        //陈老板购买
        "/d/changan/npc/obj/wrists":8,        //金复还购买
        "/d/changan/npc/obj/shield":7,        //刘老实购买
        "/d/changan/npc/obj/ring":6,          //金复还购买
        "/d/changan/npc/obj/jinjie":15,       //陈老板购买
        "/d/changan/npc/obj/baojie":15,       //陈老板购买
        "/d/changan/npc/obj/baijie":15,       //陈老板购买
        "/d/beijing/npc/obj/baojia":36,       //鳌拜
        "/clone/weapon/tiejia":1,             //暂时无处获取
        "/clone/cloth/yaodai":30,             //陈家洛、余鱼同
        "/clone/cloth/tiejia":5,              //很多
        "/clone/book/book-iron":18,           //打铁僧、神龙小屋、侠客岛书房、雪山藏经阁、燕子钨还施水阁
]);

int check_value(string filename)
{
        if (undefinedp(armor_obj[filename])) return 0;
        return armor_obj[filename];
}
