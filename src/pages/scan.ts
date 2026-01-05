import type { APIRoute } from 'astro';

export const GET: APIRoute = async () => {
  const networks = [
    { ssid: 'Dev Network 1', rssi: -45, channel: 1, auth: 'WPA2' },
    { ssid: 'Dev Network 2', rssi: -70, channel: 6, auth: 'OPEN' },
    { ssid: 'Dev Network 3', rssi: -85, channel: 11, auth: 'WPA3' }
  ];

  return new Response(JSON.stringify(networks), {
    status: 200,
    headers: {
      "Content-Type": "application/json"
    }
  });
}
