# Solar Plant Watering System built with Arduino

Battery life calculator:

https://www.digikey.de/en/resources/conversion-calculators/conversion-calculator-battery-life

Arduino documentation:

https://www.arduino.cc/reference/en/language/functions/digital-io/digitalwrite/

https://docs.arduino.cc/learn/microcontrollers/digital-pins

Solar Power Manager Waveshare (wiki, datasheet)

https://www.waveshare.com/product/modules/solar-power-manager.htm

IDE, VS Code:

https://code.visualstudio.com/ 

VS Code Extension, Platform IO:

https://platformio.org/install/ide?install=vscode

GxEPD2 library Github

https://github.com/ZinggJM/GxEPD2


Used for circuit drawings:

https://fritzing.org/


## Components list

| Amount | Description | Link |
| ----------- | ----------- | ----------- |
|1x|Epaper display 2.9 Inch Epaper Modul | https://de.aliexpress.com/item/1005004617824133.html?spm=a2g0o.productlist.main.25.45a93583sWOFOR&algo_pvid=42e690ac-add2-4249-b54f-315f9d26e110&algo_exp_id=42e690ac-add2-4249-b54f-315f9d26e110-12&pdp_npi=3%40dis%21EUR%2114.26%2111.55%21%21%21%21%21%40214528be16851114736163576d076c%2112000029851036446%21sea%21DE%210&curPageLogUid=v2SHIqHgEITO |
|1x|Arduino nano (optional: Expansion board)| https://de.aliexpress.com/item/1005004617824133.html?spm=a2g0o.productlist.main.25.45a93583sWOFOR&algo_pvid=42e690ac-add2-4249-b54f-315f9d26e110&algo_exp_id=42e690ac-add2-4249-b54f-315f9d26e110-12&pdp_npi=3%40dis%21EUR%2114.26%2111.55%21%21%21%21%21%40214528be16851114736163576d076c%2112000029851036446%21sea%21DE%210&curPageLogUid=v2SHIqHgEITO |
|1x|Solar Power manager waveshare| https://de.aliexpress.com/item/1005004502446555.html?spm=a2g0o.productlist.main.19.17d5633aKWl372&algo_pvid=c2e7cacf-30be-4a57-a757-63fa3489572f&algo_exp_id=c2e7cacf-30be-4a57-a757-63fa3489572f-10&pdp_npi=3%40dis%21EUR%2115.18%218.33%21%21%21%21%21%40214528be16851729245793920d076c%2112000029388612265%21sea%21DE%210&curPageLogUid=el5HMSAH0Aup |
|1x|14500 battery for solar power manager| https://de.aliexpress.com/item/1005002166104063.html?spm=a2g0o.detail.1000014.23.71c068f74b5cLz&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40000.333918.0&scm_id=1007.40000.333918.0&scm-url=1007.40000.333918.0&pvid=6bcdfb38-1ff9-44b4-8b6c-cd17baef3299&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40000.333918.0,pvid:6bcdfb38-1ff9-44b4-8b6c-cd17baef3299,tpp_buckets:668%232846%238109%23263&pdp_npi=3%40dis%21EUR%216.08%213.95%21%21%21%21%21%40211b444316851728897492146eb223%2112000018922784583%21rec%21DE%21 |
|1x|14500 battery for solar power manager| https://de.aliexpress.com/item/1005002166104063.html?spm=a2g0o.detail.1000014.23.71c068f74b5cLz&gps-id=pcDetailBottomMoreOtherSeller&scm=1007.40000.333918.0&scm_id=1007.40000.333918.0&scm-url=1007.40000.333918.0&pvid=6bcdfb38-1ff9-44b4-8b6c-cd17baef3299&_t=gps-id:pcDetailBottomMoreOtherSeller,scm-url:1007.40000.333918.0,pvid:6bcdfb38-1ff9-44b4-8b6c-cd17baef3299,tpp_buckets:668%232846%238109%23263&pdp_npi=3%40dis%21EUR%216.08%213.95%21%21%21%21%21%40211b444316851728897492146eb223%2112000018922784583%21rec%21DE%21 |
|1x|6V Solar panel 750mA| https://de.aliexpress.com/item/1005002326120433.html?spm=a2g0o.productlist.main.5.294865e3Ikzwh6&algo_pvid=0749a7e9-d580-48c9-ac43-b9a4d0b3bcee&aem_p4p_detail=202305270032387898518033595280006144314&algo_exp_id=0749a7e9-d580-48c9-ac43-b9a4d0b3bcee-2&pdp_npi=3%40dis%21EUR%2122.65%2112.23%21%21%21%21%21%402100baf316851727584552571d0774%2112000020099392681%21sea%21DE%210&curPageLogUid=rJUDsyZp85wA&p4p_pvid=202305270032387898518033595280006144314_3 |
|1x|**Option 1, buy the Set:** Capacitive Soil moisture sensors, 4 channel relay, water pumps | https://de.aliexpress.com/item/1005004883806299.html?spm=a2g0o.productlist.main.27.3b8829d56UTQhi&algo_pvid=865e5dc3-f460-4a22-9787-9240f20d9357&algo_exp_id=865e5dc3-f460-4a22-9787-9240f20d9357-13&pdp_npi=3%40dis%21EUR%2110.73%217.51%21%21%21%21%21%402100bfe316851115430548249d0745%2112000030882674489%21sea%21DE%210&curPageLogUid=EVobKUv7Xypc |
|4x|**Option 2, buy each component:** Water pump | https://de.aliexpress.com/item/32894401053.html?spm=a2g0o.productlist.main.21.60b4171ce6FAyb&algo_pvid=0bb46303-e11b-48ae-aadc-16a070d131aa&algo_exp_id=0bb46303-e11b-48ae-aadc-16a070d131aa-10&pdp_npi=3%40dis%21EUR%211.76%211.67%21%21%21%21%21%402100b77316851730343803536d0753%2165766185249%21sea%21DE%210&curPageLogUid=qzupIT60mWhW |
|1x|**Option 2, buy each component:** 4 channel relay| https://de.aliexpress.com/item/33038634587.html?spm=a2g0o.productlist.main.13.762c3c60Sbo6Co&algo_pvid=7dd58c14-edd9-4408-be4f-21eb0cf62515&aem_p4p_detail=202305270032151741749160589240006230843&algo_exp_id=7dd58c14-edd9-4408-be4f-21eb0cf62515-6&pdp_npi=3%40dis%21EUR%210.76%210.69%21%21%21%21%21%402100b78b16851727356672811d07b2%2167329513675%21sea%21DE%210&curPageLogUid=7ssF3zmyVYZS&p4p_pvid=202305270032151741749160589240006230843_7 |
|4x|**Option 2, buy each component:** Capacitive Soil moisture sensor | https://de.aliexpress.com/item/1005004819365767.html?spm=a2g0o.detail.1000060.2.65912456LkKou6&gps-id=pcDetailBottomMoreThisSeller&scm=1007.13339.291025.0&scm_id=1007.13339.291025.0&scm-url=1007.13339.291025.0&pvid=a3ebdfe6-69e3-457e-b593-db0135cc4127&_t=gps-id%3ApcDetailBottomMoreThisSeller%2Cscm-url%3A1007.13339.291025.0%2Cpvid%3Aa3ebdfe6-69e3-457e-b593-db0135cc4127%2Ctpp_buckets%3A668%232846%238109%231935&pdp_npi=3%40dis%21EUR%210.75%210.52%21%21%21%21%21%40211b444316851726957077122eb223%2112000030608627682%21rec%21DE%21&gatewayAdapt=glo2deu |
|1x|**Option 2, buy each component:** water hose (choose correct size, fitting to your water pumps) | https://www.aliexpress.us/item/3256801690287960.html?spm=a2g0o.productlist.main.7.a7147cd5bh4fnB&algo_pvid=7f28ff01-e44f-48aa-974f-dc46e866e2e2&aem_p4p_detail=202305310403221389360746435530000161482&algo_exp_id=7f28ff01-e44f-48aa-974f-dc46e866e2e2-3&pdp_npi=3%40dis%21USD%213.34%212.84%21%21%21%21%21%402100bbf516855310028117969d0745%2112000032540955678%21sea%21US%210&curPageLogUid=3xzFwCqp4QUj&p4p_pvid=202305310403221389360746435530000161482_4 |
