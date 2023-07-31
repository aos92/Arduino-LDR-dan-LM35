// V 0.09
// https://github.com/aos92/Arduino-LDR-dan-LM35
// https://wokwi.com/projects/371738548361828353

// Pin
const int pinLDR1 = A0; // Sensor LDR pertama
const int pinLDR2 = A1; // Sensor LDR kedua
const int pinLM35 = A2; // Sensor LM35

// Variabel Filter Kalman
const double varianKesalahanPengukuran = 10; // Varians dari kesalahan pengukuran
const double faktorKonversi = 1.00; // Faktor konversi dari pembacaan sensor LDR ke intensitas cahaya
const double varianKesalahanProses = 0.01; // Varians dari kesalahan proses
const int terang_maksimal = 1010; // Nilai kalibrasi cahaya paling terang
const float gelap_mimnimal = 3; // Nilai kalibrasi cahaya paling gelap

// Parameter sensor LDR yang disesuaikan
const double koefisienKalibrasi = 1.10; // Nilai koefisien kalibrasi yang sesuai dengan karakteristik sensor LDR
const double offsetLDR = 5; // Nilai offset untuk koreksi sensor LDR

double suhuCelcius = 0.0;

// Koefisien Gain Kalman yang dapat diubah secara dinamis
double koefisienGainKalman = 0.2; // Nilai koefisien Gain Kalman awal

// Fungsi untuk menghitung koefisien Gain Kalman berdasarkan kondisi lingkungan
double hitungKoefisienGainKalman() {
  // Contoh: ubah koefisienGainKalman berdasarkan suhu lingkungan yang dideteksi oleh LM35
  double nilaiLM35 = analogRead(pinLM35);
  suhuCelcius = ((nilaiLM35 * 5.0 / 1023.0) * 100.0) + 0.7;
        
  if (suhuCelcius > 25) {
    return 0.1;
  } else {
    return koefisienGainKalman; // Jika tidak ada perubahan, kembalikan nilai sebelumnya
  }
}

double filterKalman(double pembacaanSensor, double kovariansiKesalahanPrediksi, double pembacaanTersesuaikan) {
  double gainKalman = kovariansiKesalahanPrediksi * faktorKonversi / (faktorKonversi * kovariansiKesalahanPrediksi * faktorKonversi + varianKesalahanPengukuran);

  // Perbarui estimasi dengan menggunakan koefisienGainKalman yang sudah diubah
  pembacaanTersesuaikan = pembacaanTersesuaikan + koefisienGainKalman * (pembacaanSensor - faktorKonversi * pembacaanTersesuaikan);

  // Batasi nilai intensitas cahaya yang disesuaikan
  if (pembacaanTersesuaikan > terang_maksimal) {
    pembacaanTersesuaikan = terang_maksimal;
  } else if (pembacaanTersesuaikan < gelap_mimnimal) {
    pembacaanTersesuaikan = gelap_mimnimal;
  }

  // Perbarui kovariansi kesalahan prediksi
  kovariansiKesalahanPrediksi = (1 - koefisienGainKalman * faktorKonversi) * kovariansiKesalahanPrediksi + varianKesalahanProses;

  return pembacaanTersesuaikan;
}

void setup() {
  Serial.begin(9600);
}

void loop() {
  int nilaiLDR1 = analogRead(pinLDR1); // Baca nilai dari sensor LDR pertama
  int nilaiLDR2 = analogRead(pinLDR2); // Baca nilai dari sensor LDR kedua

  // Validasi pembacaan sensor LDR
  if (nilaiLDR1 < 0 || nilaiLDR1 > 1023 || nilaiLDR2 < 0 || nilaiLDR2 > 1023) {
    Serial.println("Kesalahan: Pembacaan sensor LDR di luar rentang yang diharapkan!");
    return; // Jangan lanjutkan dengan perhitungan jika ada kesalahan
  }

  // Koreksi nilai LDR menggunakan koefisien kalibrasi dan offset
  double nilaiLDRKoreksi1 = nilaiLDR1 * koefisienKalibrasi + offsetLDR;
  double nilaiLDRKoreksi2 = nilaiLDR2 * koefisienKalibrasi + offsetLDR;

  double intensitasCahaya1 = nilaiLDRKoreksi1 * faktorKonversi; // Konversi nilai LDR pertama yang dikoreksi menjadi intensitas cahaya
  double intensitasCahaya2 = nilaiLDRKoreksi2 * faktorKonversi; // Konversi nilai LDR kedua yang dikoreksi menjadi intensitas cahaya

  // Perbarui koefisienGainKalman berdasarkan kondisi lingkungan (suhu lingkungan)
  koefisienGainKalman = hitungKoefisienGainKalman();

  // Variabel untuk menyimpan kovariansi kesalahan prediksi dan pembacaan tersesuaikan untuk setiap sensor LDR
  static double kovariansiKesalahanPrediksi1 = 0;
  static double kovariansiKesalahanPrediksi2 = 0;
  static double pembacaanTersesuaikan1 = 0;
  static double pembacaanTersesuaikan2 = 0;

  // Terapkan filter Kalman pada sensor LDR pertama
  pembacaanTersesuaikan1 = filterKalman(intensitasCahaya1, kovariansiKesalahanPrediksi1, pembacaanTersesuaikan1);

  // Terapkan filter Kalman pada sensor LDR kedua
  pembacaanTersesuaikan2 = filterKalman(intensitasCahaya2, kovariansiKesalahanPrediksi2, pembacaanTersesuaikan2);

  // Validasi hasil intensitas cahaya yang disesuaikan
  if (pembacaanTersesuaikan1 < gelap_mimnimal || pembacaanTersesuaikan1 > terang_maksimal || pembacaanTersesuaikan2 < gelap_mimnimal || pembacaanTersesuaikan2 > terang_maksimal) {
    Serial.println("Kesalahan: Intensitas cahaya yang disesuaikan di luar rentang yang diharapkan!");
    return; // Jangan lanjutkan dengan perhitungan jika ada kesalahan
  }

  // Tampilkan hasil pengukuran
  Serial.print("Pembacaan Sensor LDR 1: ");
  Serial.print(nilaiLDR1);
  Serial.print("  Intensitas Cahaya LDR 1: ");
  Serial.print(intensitasCahaya1);
  Serial.print("  Intensitas Tersesuaikan LDR 1: ");
  Serial.print(pembacaanTersesuaikan1);
  Serial.print("  Pembacaan Sensor LDR 2: ");
  Serial.print(nilaiLDR2);
  Serial.print("  Intensitas Cahaya LDR 2: ");
  Serial.print(intensitasCahaya2);
  Serial.print("  Intensitas Tersesuaikan LDR 2: ");
  Serial.print(pembacaanTersesuaikan2);

  // Tampilkan hasil suhu yang sudah dihitung sebelumnya
  Serial.print("  Suhu (Celcius): ");
  Serial.println(suhuCelcius);

  delay(1000); // Jeda 1 detik untuk pengukuran berikutnya
}
    
