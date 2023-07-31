# Arduino-LDR-dan-LM35


Skrip Filter Kalman untuk Pengukuran Intensitas Cahaya

Skrip ini adalah implementasi filter Kalman untuk mengukur intensitas cahaya dari sensor LDR (Light Dependent Resistor) dalam lingkungan tertentu. Filter Kalman adalah metode pengolahan sinyal yang dapat mengurangi noise atau ketidakpastian dalam pembacaan sensor, sehingga menghasilkan estimasi yang lebih akurat dari intensitas cahaya yang sebenarnya.

# Variabel dan Konstanta Konfigurasi

Pada awal skrip, terdapat definisi variabel dan konstanta yang dapat disesuaikan dengan kebutuhan pengguna. Beberapa variabel yang dapat diatur adalah:

## Variabel 

• varianKesalahanPengukuran

Misalnya, nilai varianKesalahanPengukuran saat ini adalah 10, yang mengindikasikan bahwa kesalahan pengukuran diperkirakan memiliki varians sebesar 10. Ini mempengaruhi seberapa cepat filter Kalman akan merespons perubahan dalam pembacaan sensor.

Jika Anda ingin membuat filter Kalman lebih responsif terhadap perubahan cepat dalam pembacaan sensor, Anda bisa mengurangi nilai varianKesalahanPengukuran menjadi misalnya 5. Dengan nilai yang lebih kecil, filter akan lebih cepat menyesuaikan diri dengan perubahan pembacaan sensor yang cepat.

Contoh jika Anda mengubah nilai varianKesalahanPengukuran:

// Pengaturan lebih responsif const double 
varianKesalahanPengukuran = 5;

Atau jika Anda ingin membuat filter Kalman lebih tahan terhadap perubahan cepat dan ingin mengurangi sensitivitasnya, Anda bisa meningkatkan nilai varianKesalahanPengukuran menjadi misalnya 15.

Contoh jika Anda mengubah nilai varianKesalahanPengukuran:

// Pengaturan lebih tahan terhadap perubahan cepat const double 
varianKesalahanPengukuran = 15;

Perubahan nilai ini akan mempengaruhi perilaku filter Kalman dalam menyesuaikan pembacaan sensor terhadap perubahan dalam cahaya sekitar. Ingatlah untuk melakukan pengujian lebih lanjut setelah mengubah nilai untuk memastikan bahwa kinerjanya sesuai dengan harapan Anda.

• faktorKonversi

Misalnya, nilai faktorKonversi saat ini adalah 1.00. Ini berarti pembacaan sensor LDR dikonversi secara langsung menjadi intensitas cahaya dalam lux tanpa perubahan. Nilai ini harus disesuaikan berdasarkan karakteristik sensor LDR yang Anda gunakan dan satuan pengukuran yang diinginkan.

Jika Anda mengetahui karakteristik khusus dari sensor LDR Anda atau ingin mengubah satuan pengukuran intensitas cahaya, Anda dapat menyesuaikan nilai faktorKonversi.

Contoh jika Anda mengubah nilai faktorKonversi untuk mengkonversi pembacaan sensor LDR menjadi intensitas cahaya dalam satuan yang berbeda (misalnya, mikrolux):

// Mengkonversi pembacaan sensor LDR menjadi intensitas cahaya dalam mikrolux 
const double faktorKonversi = 0.001;

Contoh jika Anda mengubah nilai faktorKonversi untuk mengubah skala intensitas cahaya (misalnya, menjadi kilolux):

// Mengkonversi pembacaan sensor LDR menjadi intensitas cahaya dalam kilolux 
const double faktorKonversi = 0.001;

Dalam contoh di atas, pembacaan sensor LDR akan dikalikan dengan faktor 0.001 untuk mengubah satuan intensitas cahaya menjadi mikrolux atau kilolux, sesuai dengan nilai faktorKonversi yang baru.

Pastikan untuk menyesuaikan nilai faktorKonversi berdasarkan karakteristik sensor LDR dan satuan pengukuran yang sesuai dengan kebutuhan Anda. Jangan lupa untuk melakukan pengujian lebih lanjut untuk memastikan bahwa pembacaan intensitas cahaya telah diubah sesuai dengan harapan Anda setelah mengubah nilai faktorKonversi.

• varianKesalahanProses

Misalnya, nilai varianKesalahanProses saat ini adalah 0.01. Nilai ini mengontrol seberapa besar varians dari kesalahan proses yang diperkirakan ketika filter Kalman memperbarui estimasi pembacaan sensor. Nilai ini mempengaruhi bagaimana filter merespons perubahan dalam pembacaan sensor dari waktu ke waktu.

Jika Anda ingin membuat filter Kalman lebih reaktif terhadap perubahan dalam pembacaan sensor, Anda bisa mengurangi nilai varianKesalahanProses. Dengan nilai yang lebih kecil, filter akan lebih cepat menyesuaikan diri dengan perubahan pembacaan sensor.

Contoh jika Anda mengubah nilai varianKesalahanProses untuk membuat filter lebih reaktif:

// Filter lebih reaktif terhadap perubahan pembacaan sensor const double 
varianKesalahanProses = 0.005;

Atau jika Anda ingin membuat filter lebih halus dan lebih tahan terhadap perubahan cepat dalam pembacaan sensor, Anda bisa meningkatkan nilai varianKesalahanProses.

Contoh jika Anda mengubah nilai varianKesalahanProses untuk membuat filter lebih halus:

// Filter lebih halus dan lebih tahan terhadap perubahan cepat const double 
varianKesalahanProses = 0.02;

Perubahan nilai varianKesalahanProses ini akan mempengaruhi perilaku filter Kalman dalam menyesuaikan pembacaan sensor dari waktu ke waktu. Ingatlah untuk melakukan pengujian lebih lanjut setelah mengubah nilai ini untuk memastikan bahwa kinerja filter sesuai dengan harapan Anda. Selalu pertimbangkan kondisi dan kebutuhan Anda ketika mengatur ulang parameter ini.

• terang_maksimal dan gelap_mimnimal:

Misalnya, nilai terang_maksimal saat ini adalah 1010 dan nilai gelap_mimnimal adalah 3. Nilai-nilai ini mengontrol batas atas dan batas bawah intensitas cahaya yang diizinkan setelah disesuaikan oleh filter Kalman. Nilai-nilai ini harus disesuaikan berdasarkan rentang intensitas cahaya yang diharapkan dari lingkungan Anda.

Jika Anda berada di lingkungan yang memiliki cahaya yang sangat terang, Anda mungkin ingin meningkatkan nilai terang_maksimal untuk memungkinkan intensitas cahaya yang lebih tinggi.

Contoh jika Anda mengubah nilai terang_maksimal:

// Lingkungan dengan cahaya yang sangat terang
const int terang_maksimal = 1500;

Jika Anda berada di lingkungan yang memiliki cahaya yang sangat redup, Anda mungkin ingin menurunkan nilai terang_maksimal untuk membatasi intensitas cahaya yang disesuaikan agar tidak terlalu tinggi.

Contoh jika Anda mengubah nilai terang_maksimal:

// Lingkungan dengan cahaya yang sangat redup 
const int terang_maksimal = 800;

Selain itu, jika Anda ingin membatasi rentang intensitas cahaya yang disesuaikan ke nilai yang lebih rendah, Anda bisa mengubah nilai gelap_mimnimal menjadi misalnya 1.

Contoh jika Anda mengubah nilai gelap_mimnimal:

// Batas bawah intensitas cahaya yang lebih rendah 
const float gelap_mimnimal = 1;

Pastikan untuk melakukan pengujian lebih lanjut setelah mengubah nilai-nilai ini untuk memastikan bahwa batas atas dan bawah intensitas cahaya yang disesuaikan sesuai dengan kebutuhan dan lingkungan Anda. Tetap perhatikan kondisi lingkungan sekitar dan gunakan nilai-nilai yang sesuai dengan karakteristik sensor dan pengaturan yang diinginkan.

• offsetLDR

Misalnya, nilai koefisienKalibrasi saat ini adalah 1.10 dan nilai offsetLDR adalah 5. Nilai-nilai ini digunakan untuk mengkalibrasi pembacaan sensor LDR sehingga pembacaan yang sebenarnya dari sensor dapat dikompensasi atau diubah untuk meningkatkan akurasi atau mengubah resolusi pembacaan.

Jika Anda menemukan bahwa pembacaan sensor LDR cenderung memiliki ketidakakuratan yang terukur, Anda bisa menyesuaikan nilai koefisienKalibrasi untuk mengkalibrasi pembacaan LDR.

Contoh jika Anda mengubah nilai koefisienKalibrasi:

// Mengkalibrasi pembacaan sensor LDR dengan faktor 1.05 
const double koefisienKalibrasi = 1.05;

Atau jika Anda ingin memperbaiki ketidakakuratan sensor LDR, Anda bisa menyesuaikan nilai offsetLDR.

Contoh jika Anda mengubah nilai offsetLDR:

// Memperbaiki ketidakakuratan sensor LDR dengan offset -2 
const double offsetLDR = -2;

Pastikan untuk mengambil data dan melakukan percobaan lebih lanjut untuk menentukan nilai yang tepat untuk koefisienKalibrasi dan offsetLDR agar sesuai dengan karakteristik sensor LDR yang Anda gunakan dan untuk mencapai akurasi atau resolusi yang diinginkan.

Sesuaikan nilai-nilai ini dengan hati-hati karena perubahan yang tidak tepat dapat menyebabkan pembacaan sensor menjadi tidak akurat atau bahkan tidak berfungsi dengan baik. Selalu pertimbangkan kondisi lingkungan sekitar dan gunakan nilai-nilai yang sesuai dengan karakteristik sensor dan tujuan penggunaan.



## Fungsi

• Alur dari fungsi hitungKoefisienGainKalman() adalah sebagai berikut:

1. Baca nilai sensor LM35 dengan menggunakan fungsi analogRead(pinLM35). Nilai ini akan mewakili pembacaan suhu dari sensor LM35 dalam bentuk angka antara 0 hingga 1023.

2. Ubah nilai sensor LM35 menjadi suhu dalam derajat Celcius menggunakan rumus berikut: suhuCelcius = ((nilaiLM35 * 5.0 / 1023.0) * 100.0) + 0.7. Proses ini mengonversi pembacaan analog menjadi suhu dalam derajat Celcius dengan asumsi bahwa tegangan referensi adalah 5V dan suhu sebenarnya pada 0°C adalah 0.7°C. Hasil konversi disimpan dalam variabel suhuCelcius.

3. Setelah mendapatkan nilai suhu dalam variabel suhuCelcius, dilakukan pemrosesan kondisional untuk menentukan nilai koefisienGainKalman. Dalam contoh di atas, jika suhuCelcius lebih besar dari 25°C, maka nilai koefisienGainKalman akan diubah menjadi 0.1. Ini berarti filter Kalman akan lebih merespons perubahan pembacaan sensor dengan cepat saat suhu lingkungan lebih tinggi dari 25°C.

4. Jika suhuCelcius tidak lebih besar dari 25°C, maka nilai koefisienGainKalman akan tetap sama seperti sebelumnya. Ini berarti filter Kalman akan tetap memiliki koefisien Gain yang sama seperti sebelumnya, dan tidak ada perubahan responsivitas filter Kalman saat suhu lingkungan tidak melebihi 25°C.

Jadi, fungsi hitungKoefisienGainKalman() bertujuan untuk mengubah koefisien Gain Kalman (koefisienGainKalman) berdasarkan suhu lingkungan yang dideteksi oleh sensor LM35. Perubahan ini memberikan cara untuk menyesuaikan responsivitas filter Kalman terhadap perubahan pembacaan sensor berdasarkan perubahan suhu lingkungan. Jika suhu lingkungan lebih tinggi dari 25°C, responsivitas filter akan meningkat dengan mengurangi nilai koefisien Gain (koefisienGainKalman) menjadi 0.1. Jika suhu lingkungan tidak melebihi 25°C, responsivitas filter akan tetap sama seperti sebelumnya.

• Alur dari fungsi filterKalman() adalah sebagai berikut:

1. Hitung nilai gainKalman berdasarkan kovariansi kesalahan prediksi (kovariansiKesalahanPrediksi), faktor konversi (faktorKonversi), dan varian kesalahan pengukuran (varianKesalahanPengukuran). Nilai gainKalman akan digunakan untuk memperbarui estimasi intensitas cahaya pada langkah selanjutnya.

2. Perbarui estimasi intensitas cahaya yang disesuaikan (pembacaanTersesuaikan) dengan menggunakan koefisienGainKalman, yang telah diubah sebelumnya berdasarkan suhu lingkungan, dan perbedaan antara pembacaan sensor saat ini (pembacaanSensor) dengan estimasi intensitas cahaya yang disesuaikan sebelumnya (pembacaanTersesuaikan). Langkah ini merupakan langkah pembaruan dari filter Kalman yang menggabungkan informasi dari pembacaan sensor terbaru dan estimasi sebelumnya untuk menghasilkan nilai intensitas cahaya yang diperbarui.

3. Batasi nilai intensitas cahaya yang disesuaikan agar tetap berada dalam batas yang ditentukan oleh terang_maksimal dan gelap_mimnimal. Jika nilai intensitas cahaya yang disesuaikan melebihi terang_maksimal, maka nilai tersebut akan diatur kembali menjadi terang_maksimal. Jika nilai intensitas cahaya yang disesuaikan kurang dari gelap_mimnimal, maka nilai tersebut akan diatur kembali menjadi gelap_mimnimal. Hal ini bertujuan untuk membatasi nilai intensitas cahaya yang dihasilkan oleh filter agar tetap berada dalam rentang yang diharapkan.

4. Perbarui kovariansi kesalahan prediksi dengan menghitung nilai baru berdasarkan koefisienGainKalman, faktorKonversi, dan varian kesalahan proses (varianKesalahanProses). Langkah ini membantu mengestimasi sejauh mana pembacaan sensor yang sebenarnya mungkin berbeda dari estimasi sebelumnya.

5. Kembalikan nilai intensitas cahaya yang disesuaikan sebagai hasil dari fungsi filterKalman().

Fungsi filterKalman() bertujuan untuk menerapkan filter Kalman pada pembacaan sensor intensitas cahaya dari LDR. Filter Kalman digunakan untuk mereduksi noise atau ketidakpastian dalam pembacaan sensor dan menghasilkan estimasi yang lebih akurat dari intensitas cahaya yang sebenarnya. Selain itu, filter Kalman juga dapat menyesuaikan respons filter terhadap perubahan pembacaan sensor berdasarkan nilai koefisien yang dihitung oleh fungsi hitungKoefisienGainKalman() berdasarkan suhu lingkungan yang dideteksi oleh sensor LM35.

• Alur dari fungsi setup() adalah sebagai berikut:

1. Digunakan untuk inisialisasi dan pengaturan awal, seperti membuka komunikasi serial.

• Alur dari fungsi loop() adalah sebagai berikut:

1. Baca nilai dari dua sensor LDR, yaitu nilaiLDR1 dan nilaiLDR2, menggunakan fungsi analogRead(). Nilai-nilai ini mewakili pembacaan analog dari kedua sensor LDR.

2. Lakukan validasi pembacaan sensor LDR dengan memeriksa apakah nilai nilaiLDR1 dan nilaiLDR2 berada di dalam rentang yang diharapkan (0 hingga 1023). Jika ada kesalahan atau nilai di luar rentang yang diharapkan, pesan kesalahan akan ditampilkan melalui Serial Monitor, dan proses perhitungan akan dihentikan dengan menggunakan pernyataan return.

3. Koreksi nilai sensor LDR menggunakan koefisienKalibrasi dan offsetLDR. Nilai-nilai ini digunakan untuk mengkalibrasi pembacaan sensor LDR sehingga pembacaan yang sebenarnya dari sensor dapat dikompensasi atau diubah untuk meningkatkan akurasi atau mengubah resolusi pembacaan. Hasil koreksi disimpan dalam variabel nilaiLDRKoreksi1 dan nilaiLDRKoreksi2.

4. Konversi nilai sensor LDR yang telah dikoreksi (nilaiLDRKoreksi1 dan nilaiLDRKoreksi2) menjadi intensitas cahaya menggunakan faktorKonversi. Nilai intensitas cahaya yang dihasilkan disimpan dalam variabel intensitasCahaya1 dan intensitasCahaya2.

5. Perbarui nilai koefisienGainKalman berdasarkan kondisi lingkungan (suhu lingkungan) dengan menggunakan fungsi hitungKoefisienGainKalman(). Nilai ini akan digunakan nanti saat menerapkan filter Kalman pada sensor LDR.

6. Variabel kovariansiKesalahanPrediksi1, kovariansiKesalahanPrediksi2, pembacaanTersesuaikan1, dan pembacaanTersesuaikan2 digunakan untuk menyimpan kovariansi kesalahan prediksi dan pembacaan intensitas cahaya yang disesuaikan untuk setiap sensor LDR.

7. erapkan filter Kalman pada sensor LDR pertama dan kedua dengan memanggil fungsi filterKalman() untuk masing-masing sensor. Filter Kalman digunakan untuk mereduksi noise atau ketidakpastian dalam pembacaan sensor dan menghasilkan estimasi yang lebih akurat dari intensitas cahaya yang sebenarnya. Hasil dari masing-masing filter Kalman disimpan dalam variabel pembacaanTersesuaikan1 dan pembacaanTersesuaikan2.

8. Validasi hasil intensitas cahaya yang disesuaikan untuk memastikan bahwa nilai-nilai tersebut berada dalam batas yang ditentukan oleh terang_maksimal dan gelap_mimnimal. Jika ada kesalahan, pesan kesalahan akan ditampilkan melalui Serial Monitor, dan proses perhitungan akan dihentikan dengan menggunakan pernyataan return.

9. Tampilkan hasil pengukuran termasuk nilai sensor LDR asli (nilaiLDR1 dan nilaiLDR2), intensitas cahaya yang dihitung (intensitasCahaya1 dan intensitasCahaya2), dan intensitas cahaya yang disesuaikan oleh filter Kalman (pembacaanTersesuaikan1 dan pembacaanTersesuaikan2). Juga tampilkan nilai suhu yang sudah dihitung sebelumnya 

10. Tunggu selama 1 detik menggunakan fungsi delay(1000) sebelum melakukan pengukuran berikutnya. Ini memberikan jeda waktu antara pengukuran untuk menghindari pembacaan yang terlalu sering.



## Penerapan rumus:

gainKalman = kovariansiKesalahanPrediksi * faktorKonversi / (faktorKonversi * kovariansiKesalahanPrediksi + varianKesalahanPengukuran);

Dimana:

- gainKalman: Variabel yang menyimpan nilai koefisien gain dari filter Kalman.

- kovariansiKesalahanPrediksi: Variabel yang menyimpan nilai kovariansi kesalahan prediksi.

- faktorKonversi: Nilai faktor konversi yang digunakan untuk mengkonversi pembacaan sensor LDR menjadi intensitas cahaya.

- varianKesalahanPengukuran: Variabel yang menyimpan nilai varian kesalahan pengukuran.

Dalam rumus ini, kita menggunakan nilai kovariansiKesalahanPrediksi dan varianKesalahanPengukuran untuk menghitung koefisien gain (gainKalman) yang digunakan dalam perbaruan estimasi filter Kalman. Koefisien gain ini mempengaruhi sejauh mana pembacaan sensor yang sebenarnya diprioritaskan dibandingkan dengan estimasi sebelumnya dalam perhitungan nilai intensitas cahaya yang disesuaikan. Semakin tinggi nilai kovariansiKesalahanPrediksi, maka pembacaan sensor yang sebenarnya akan lebih berpengaruh pada perhitungan, dan semakin rendah nilai kovariansiKesalahanPrediksi, maka estimasi sebelumnya akan lebih dipertahankan


pembacaanTersesuaikan = pembacaanTersesuaikan + koefisienGainKalman * (pembacaanSensor - faktorKonversi * pembacaanTersesuaikan);

Dimana:

- pembacaanTersesuaikan: Variabel yang menyimpan estimasi yang diperbarui atau disesuaikan dari intensitas cahaya yang diukur menggunakan filter Kalman.

- koefisienGainKalman: Variabel yang menyimpan nilai koefisien gain dari filter Kalman.

- pembacaanSensor: Variabel yang menyimpan nilai intensitas cahaya yang diukur dari sensor LDR.

- faktorKonversi: Nilai faktor konversi yang digunakan untuk mengkonversi pembacaan sensor LDR menjadi intensitas cahaya.

Langkah-langkah dalam pembaruan estimasi menggunakan filter Kalman adalah sebagai berikut:

1. Hitung selisih antara nilai intensitas cahaya yang diukur (pembacaanSensor) dan estimasi sebelumnya (pembacaanTersesuaikan).

2. Kalikan selisih di atas dengan faktorKonversi. Ini dilakukan karena kita mengkonversi nilai sensor LDR ke dalam intensitas cahaya menggunakan faktorKonversi.

3. Kalikan hasil dari langkah 2 dengan koefisienGainKalman. Koefisien gain ini mempengaruhi sejauh mana perbedaan antara pembacaan sensor dan estimasi sebelumnya akan mempengaruhi pembaruan estimasi.

4. Tambahkan hasil dari langkah 3 ke estimasi sebelumnya (pembacaanTersesuaikan). Ini akan menghasilkan estimasi yang diperbarui berdasarkan perbedaan antara pembacaan sensor dan estimasi sebelumnya dengan mempertimbangkan koefisien gain.

Proses ini dilakukan pada setiap iterasi pembaruan filter Kalman untuk menghasilkan estimasi yang semakin mendekati nilai sebenarnya dari intensitas cahaya. Hal ini membantu mereduksi noise atau ketidakpastian dalam pembacaan sensor dan menghasilkan estimasi yang lebih akurat dari intensitas cahaya yang sebenarnya.


kovariansiKesalahanPrediksi = (1 - koefisienGainKalman * faktorKonversi) * kovariansiKesalahanPrediksi + varianKesalahanProses;

Dimana:

- kovariansiKesalahanPrediksi: Variabel yang menyimpan nilai kovariansi kesalahan prediksi.

- koefisienGainKalman: Variabel yang menyimpan nilai koefisien gain dari filter Kalman.

- faktorKonversi: Nilai faktor konversi yang digunakan untuk mengkonversi pembacaan sensor LDR menjadi intensitas cahaya.

- varianKesalahanProses: Variabel yang menyimpan nilai varian kesalahan proses.

Langkah-langkah dalam pembaruan kovariansi kesalahan prediksi menggunakan filter Kalman adalah sebagai berikut:

1. Kalikan koefisienGainKalman dengan faktorKonversi. Ini dilakukan karena kita ingin mempertimbangkan sejauh mana koefisien gain mempengaruhi kovariansi kesalahan prediksi untuk pembacaan sensor LDR yang dikonversi menjadi intensitas cahaya.

2. Kurangkan hasil dari langkah 1 dari 1 (yaitu 1 - hasil dari langkah 1).

3. Kalikan hasil dari langkah 2 dengan nilai kovariansi kesalahan prediksi sebelumnya (kovariansiKesalahanPrediksi). Ini dilakukan untuk mengurangi dampak dari perubahan koefisien gain pada nilai kovariansi kesalahan prediksi yang sebelumnya.

4. Tambahkan varianKesalahanProses ke hasil dari langkah 3. varianKesalahanProses adalah nilai varian kesalahan proses yang diketahui dari sistem atau sensor.

Proses ini dilakukan pada setiap iterasi pembaruan filter Kalman untuk menghasilkan nilai kovariansi kesalahan prediksi yang diperbarui. Kovariansi kesalahan prediksi digunakan dalam perhitungan koefisien gain dan berfungsi untuk mengontrol sejauh mana pembacaan sensor yang sebenarnya diprioritaskan dibandingkan dengan estimasi sebelumnya dalam perhitungan nilai intensitas cahaya yang disesuaikan.


## Penggunaan

Pastikan Anda sudah menghubungkan sensor LDR dan sensor LM35 ke pin yang sesuai pada perangkat Anda sebelum menjalankan skrip ini. Sesuaikan variabel dan konstanta konfigurasi sesuai dengan karakteristik sensor yang Anda gunakan dan lingkungan pengujian.

## Catatan Penting

Skrip ini dikembangkan untuk penggunaan pada mikrokontroler Arduino atau platform serupa yang mendukung pemrograman bahasa C/C++.

Pastikan Anda memahami dan menyesuaikan variabel dan konstanta konfigurasi sebelum menggunakan skrip ini.

Perhatikan kesalahan atau keluaran dari skrip melalui komunikasi serial untuk mendeteksi masalah atau perbaikan yang mungkin diperlukan.

Jika terjadi masalah dengan pembacaan sensor, pastikan untuk memverifikasi koneksi dan kalibrasi sensor sesuai dengan spesifikasi yang diinginkan.

## Kredit (lanjutan)

Skrip ini dikembangkan berdasarkan konsep dan prinsip filter Kalman, sebuah algoritma estimasi yang sangat berguna untuk mengolah data sensor dengan tingkat ketidakpastian atau noise yang tinggi. Penggunaan filter Kalman memungkinkan untuk mendapatkan estimasi yang lebih akurat dan stabil dari nilai intensitas cahaya yang diukur oleh sensor LDR.

## Catatan Tambahan

Pastikan Anda memiliki pemahaman yang memadai tentang filter Kalman sebelum menggunakan skrip ini. Jika Anda tidak familiar dengan konsepnya, disarankan untuk mempelajari dasar-dasar filter Kalman terlebih dahulu.

Perhatikan bahwa pengaturan variabel dan konstanta konfigurasi akan sangat mempengaruhi kinerja filter Kalman dalam mengoreksi pembacaan sensor. Lakukan eksperimen dan uji coba untuk mendapatkan hasil yang optimal sesuai dengan kebutuhan Anda.

Jika Anda ingin mengembangkan atau memodifikasi skrip ini, pastikan untuk melakukan uji coba yang cermat dan memahami implikasi dari setiap perubahan yang Anda buat.

Pastikan untuk melakukan kalibrasi sensor LDR dan sensor LM35 dengan benar untuk mendapatkan pembacaan yang akurat dan konsisten sebelum menggunakan skrip ini dalam aplikasi nyata.

## Sumber Daya

Untuk memahami lebih lanjut tentang filter Kalman dan penerapannya dalam pengolahan data sensor, Anda dapat merujuk ke sumber daya berikut:

- Buku: "Kalman Filtering: Theory and Practice Using MATLAB" oleh Mohinder S. Grewal dan Angus P. Andrews.

- Buku: "Kalman Filter for Beginners with MATLAB Examples" oleh Phil Kim.

- Artikel: "An Introduction to the Kalman Filter" oleh Greg Welch dan Gary Bishop (1995).

## Lisensi

Skrip ini dilisensikan di bawah GNU GPL V3.0. Anda bebas untuk menggunakan, mengubah, dan mendistribusikan skrip ini dalam proyek Anda selama mencantumkan kredit dan menyertakan lisensi dengan kode tersebut.

## Penulis

Skrip ini dikembangkan oleh "Asep Oman Somantri" dan diilhami oleh kontribusi dari komunitas pemrograman dan pengembangan perangkat keras.

Jika Anda memiliki pertanyaan atau masalah terkait skrip ini, silakan hubungi "asepomansomantri@gmail.com".

Terima kasih telah menggunakan skrip Filter Kalman untuk Pengukuran Intensitas Cahaya. Selamat mencoba dan semoga bermanfaat!
