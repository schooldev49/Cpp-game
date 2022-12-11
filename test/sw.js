const cacheName = "cache";
const version = 3;


self.addEventListener('install', (event) => {
    event.waitUntil(caches.open(cacheName));
})
self.addEventListener("fetch", (event) => {
    event.respondWith(caches.open(cacheName).then((cache) => {
        return cache.match(event.request.url).then((response) => {

            if (response){ // after a while
                return response;
            }
            return fetch(event.request.url).then((fetchedResponse) => {
                cache.put(event.request, fetchedResponse.clone());
                return fetchedResponse;
            })
        })
    }))
})