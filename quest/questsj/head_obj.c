// Created by Smallfish For HUAXIA@2004    2004/04/24

#include <ansi.h>

mapping head_obj = ([
        "/d/yanziwu/npc/obj/necklace":30,             //阿朱、阿碧
        "/d/xueshan/obj/sengmao":10,                  //僧帽
        "/d/xueshan/obj/rtlian":34,                   //莲座
        "/d/xueshan/obj/klguan":34,                   //莲座
        "/d/xiakedao/obj/xuantie":1,                  //侠客岛一律廉价
        "/d/xiakedao/obj/lingpai1":1,                 //侠客岛一律廉价
        "/d/xiakedao/obj/lingpai":1,                  //侠客岛一律廉价
        "/d/wanjiegu/npc/obj/xiu-scarf":33,           //钟灵
        "/d/wanjiegu/npc/obj/scarf":1,                //暂时无处获取
        "/d/wanjiegu/npc/obj/hat":1,                  //暂时无处获取
        "/d/taohuacun/obj/rose":1,                    //暂时无处获取
        "/d/taohua/obj/shudai":30,                    //黄蓉、郭芙
        "/d/taohua/obj/jindai":1,                     //暂时无处获取
        "/d/shenlong/obj/sg_mianzhao":1,              //暂时无处获取
        "/d/shaolin/obj/weibo":22,                    //道相禅师
        "/d/shaolin/obj/toukui":22,                   //道相禅师
        "/d/mingjiao/obj/weibo":1,                    //暂时无处获取
        "/d/mingjiao/obj/toukui":1,                   //暂时无处获取
        "/d/heimuya/npc/obj/zhenzhu":33,              //上官云
        "/d/hangzhou/npc/obj/xuannv-lingfu":9,        //倩儿
        "/d/hangzhou/npc/obj/tongxin-jie":9,          //倩儿
        "/d/hangzhou/npc/obj/sansheng-youyue":15,     //倩儿
        "/d/hangzhou/npc/obj/huangtong-suo":9,        //倩儿
        "/d/hangzhou/honghua/obj/cuiyu":33,           //霍青桐
        "/d/foshan/obj/hua3":25,                      //佛山林间道
        "/d/foshan/obj/hua2":25,                      //佛山林间道
        "/d/foshan/obj/hua1":25,                      //佛山林间道
        "/d/dali/obj/chahua9":25,                     //茶花园
        "/d/dali/obj/chahua8":25,                     //茶花园
        "/d/dali/obj/chahua7":25,                     //茶花园
        "/d/dali/obj/chahua6":25,                     //茶花园
        "/d/dali/obj/chahua5":25,                     //茶花园
        "/d/dali/obj/chahua4":25,                     //茶花园
        "/d/dali/obj/chahua3":25,                     //茶花园
        "/d/dali/obj/chahua2":25,                     //茶花园
        "/d/dali/obj/chahua13":25,                    //茶花园
        "/d/dali/obj/chahua12":25,                    //茶花园
        "/d/dali/obj/chahua11":25,                    //茶花园
        "/d/dali/obj/chahua10":25,                    //茶花园
        "/d/dali/obj/chahua1":25,                     //茶花园
        "/d/dali/npc/obj/ttoujin":22,                 //台夷猎手（三个）、台夷商贩（三个）、大理渔夫
        "/d/dali/npc/obj/lace":36,                    //大土司
        "/d/city/obj/yrose":5,                        //杨永福购买
        "/d/city/obj/toukui":1,                       //暂时无处获取
        "/d/city/obj/rrose":5,                        //杨永福购买
        "/d/city/obj/necklace":8,                     //陈阿婆购买、小翠
        "/d/city/obj/cycle":1,                        //暂时无处获取
        "/d/city/npc/obj/toukui":5,                   //杨永福、高丽商人购买
        "/d/city/npc/obj/necklace":30,                //崔莺莺、程玉环
        "/d/city/npc/obj/cycle":5,                    //杨永福、高丽商人购买
        "/d/city/npc/cloth/xiu-scarf":5,              //曾柔购买
        "/d/city/npc/cloth/scarf":5,                  //曾柔购买
        "/d/city/npc/cloth/hat":5,                    //曾柔购买
        "/d/changan/npc/obj/zi-luolan":5,             //卖花姑娘购买
        "/d/changan/npc/obj/yupei":36,                //萧员外
        "/d/changan/npc/obj/neck":9,                  //金复还购买
        "/d/changan/npc/obj/lan-tiane":5,             //卖花姑娘购买
        "/d/changan/npc/obj/huang-meigui":5,          //卖花姑娘购买
        "/d/changan/npc/obj/hong-meigui":5,           //卖花姑娘购买
        "/d/changan/npc/obj/hei-mudan":5,             //卖花姑娘购买
        "/d/changan/npc/obj/bai-chahua":5,            //卖花姑娘购买
        "/d/beijing/npc/obj/hat":36,                  //卖花少女
        "/clone/gift/mjade":27000,
        "/clone/gift/mdiamond":27000,
        "/clone/gift/mcrystal":27000,
        "/clone/gift/magate":27000,
        "/clone/gift/fjade":9000,
        "/clone/gift/fdiamond":9000,
        "/clone/gift/fcrystal":9000,
        "/clone/gift/fagate":9000,
        "/clone/gift/diamond":3000,
        "/clone/gift/crystal":3000,
        "/clone/gift/jade":3000,
        "/clone/gift/agate":3000,
        "/clone/gift/cjade":1000,
        "/clone/gift/cdiamond":1000,
        "/clone/gift/ccrystal":1000,
        "/clone/gift/cagate":1000,
]);

int check_value(string filename)
{
        if (undefinedp(head_obj[filename])) return 0;
        return head_obj[filename];
}
